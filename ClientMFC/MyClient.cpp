#include "stdafx.h"
#include "MyClient.h"

#include "winsock2.h"  
#include <iostream>  
#include <thread>
using namespace std;

/* ************************************ friend function *************************************** */
void onRun(CMyClient* cc) {
	const int bufSz = cc->BUF_SIZE;
	cc->m_isThreadRun = true;

	while (!cc->m_toStop) {
		try {
			if (!cc->m_sendList.empty()) {
				Msg * msg = cc->m_sendList.back();
				bool isSendSucc = cc->sendMessage(msg);
				if (isSendSucc) {
					cc->m_sendList.pop_back();
					delete msg;
				}
			}
		}
		catch (CException* e) {
			TCHAR err[511];
			e->GetErrorMessage(err, 511);
		}

// 		char bufRecv[bufSz];
// 		ZeroMemory(bufRecv, cc->BUF_SIZE);
// 		recv(cc->m_socket, bufRecv, cc->BUF_SIZE, 0);// ���շ������˵����ݣ� ֻ����5���ַ�  
// 		cout << endl << "�ӷ������������ݣ�" << bufRecv;
// 		cout << "\n";
	}

	cc->m_isThreadRun = false;
}

/* ************************************ member function *************************************** */
CMyClient::CMyClient() : m_toStop(false),
							m_isStop(true),
							m_isThreadRun(false)
{
}


CMyClient::~CMyClient()
{
}

bool CMyClient::createClient() {
		WSADATA wsd;//WSADATA���� 
		SOCKADDR_IN servAddr;//��������ַ
		//��ʼ���׽��ֶ�̬��  
		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
			cout << "WSAStartup failed!" << endl;
			return false;
		}

		//�����׽���  
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == m_socket) {
			cout << "socket failed!" << endl;
			WSACleanup();//�ͷ��׽�����Դ  
			return false;
		}

		//���÷�������ַ  
		servAddr.sin_family = AF_INET;
		in_addr addr;
		inet_pton(AF_INET, "127.0.0.1", &addr);//inet_addr("127.0.0.1");
		servAddr.sin_addr.s_addr = addr.s_addr;
		servAddr.sin_port = htons((u_short)6000);
//		int nServAddlen = sizeof(servAddr);

		//���ӷ�����
		int rtn = connect(m_socket, (LPSOCKADDR)&servAddr, sizeof(servAddr));
		if (SOCKET_ERROR == rtn) {
			cout << "connect failed!" << endl;
			closesocket(m_socket);//�ر��׽���  
			WSACleanup();//�ͷ��׽�����Դ  
			return false;
		}

		m_isStop = false;

		return true;
}

void CMyClient::start() {
	std::thread t1(onRun, this);
	t1.detach();
}

bool CMyClient::sendMessage(Msg * msg) {
	//���������������
	int rtn = send(m_socket, msg->data, msg->len, 0);
	if (SOCKET_ERROR == rtn)
		return false;

	return true;
}

void CMyClient::addMessage(char * msg) {
//		m_sendList.push_back(msg);
}

void CMyClient::addMessage(Msg * msg) {
	m_sendList.push_back(msg);
}

void CMyClient::addMessage(CMsgWriter& msg) {
	char * ddd = msg.getData();
	int len = msg.getDataLen();
	addMessage(msg.getData(), msg.getDataLen());
}

void CMyClient::addMessage(char * data, int msgLen) {
	char * msgCopy = new char[msgLen];
	memcpy(msgCopy, data, msgLen);
	Msg * msg = new Msg(msgCopy, msgLen);
	addMessage(msg);
}

void CMyClient::close() {
	m_toStop = true;
	waitStopThread();

	int rtn = closesocket(m_socket);//�ر��׽���  
	if (SOCKET_ERROR == rtn) {
		rtn = 1;
	}
	WSACleanup();//�ͷ��׽�����Դ 

	m_isStop = true;
}

void CMyClient::waitStopThread() {
	while (m_isThreadRun) {
	}
}