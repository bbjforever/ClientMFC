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
// 		recv(cc->m_socket, bufRecv, cc->BUF_SIZE, 0);// 接收服务器端的数据， 只接收5个字符  
// 		cout << endl << "从服务器接收数据：" << bufRecv;
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
		WSADATA wsd;//WSADATA变量 
		SOCKADDR_IN servAddr;//服务器地址
		//初始化套结字动态库  
		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
			cout << "WSAStartup failed!" << endl;
			return false;
		}

		//创建套接字  
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == m_socket) {
			cout << "socket failed!" << endl;
			WSACleanup();//释放套接字资源  
			return false;
		}

		//设置服务器地址  
		servAddr.sin_family = AF_INET;
		in_addr addr;
		inet_pton(AF_INET, "127.0.0.1", &addr);//inet_addr("127.0.0.1");
		servAddr.sin_addr.s_addr = addr.s_addr;
		servAddr.sin_port = htons((u_short)6000);
//		int nServAddlen = sizeof(servAddr);

		//连接服务器
		int rtn = connect(m_socket, (LPSOCKADDR)&servAddr, sizeof(servAddr));
		if (SOCKET_ERROR == rtn) {
			cout << "connect failed!" << endl;
			closesocket(m_socket);//关闭套接字  
			WSACleanup();//释放套接字资源  
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
	//向服务器发送数据
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

	int rtn = closesocket(m_socket);//关闭套接字  
	if (SOCKET_ERROR == rtn) {
		rtn = 1;
	}
	WSACleanup();//释放套接字资源 

	m_isStop = true;
}

void CMyClient::waitStopThread() {
	while (m_isThreadRun) {
	}
}