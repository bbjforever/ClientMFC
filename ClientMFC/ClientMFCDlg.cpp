
// ClientMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientMFC.h"
#include "ClientMFCDlg.h"
#include "afxdialogex.h"
#include "MsgWrite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientMFCDlg �Ի���



CClientMFCDlg::CClientMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CClientMFCDlg::OnClose)
ON_BN_CLICKED(IDC_SEND, &CClientMFCDlg::OnSend)
END_MESSAGE_MAP()


// CClientMFCDlg ��Ϣ�������

BOOL CClientMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	if (m_client.createClient()) {
		m_client.start();
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientMFCDlg::OnClose()
{
	m_client.close();

	CDialogEx::OnOK();
}

void UTF_8ToUnicode(char* pOut, wchar_t* pText)
{
	// ע�� WCHAR�ߵ��ֵ�˳��,���ֽ���ǰ�����ֽ��ں�
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
}

void CClientMFCDlg::OnSend()
{
	CMsgWriter msg;
	msg.writeString("fuck", 5);
	msg.writeInt(89757);
	m_client.addMessage(msg);

	return;

	CWnd * send = GetDlgItem(IDC_CONTENT);
	CString str;
	send->GetWindowTextW(str);

	CStringW strWide = CT2CW(str); // ��T�ַ�ת���ɿ��ַ�
	WCHAR * wbuf = strWide.GetBuffer(); // ��ȡCString�ڲ�����
	int wlen = strWide.GetLength();

	int bufSz = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, NULL, 0, NULL, NULL);// wlen * 3 + 1;
	int sLen = bufSz - 1;//ת���ɵ�char�ĳ���
	int dataHeadSz = 3;/* char + short */
	bufSz += dataHeadSz;
	char * buf = new char[bufSz];
	ZeroMemory(buf, bufSz * sizeof(char));
	char * pType = buf;//char
	*pType = 1;
	char * pLen = pType + 1;//short
	*pLen = sLen >> 8;//���ֽ�
	*(pLen + 1) = sLen;//���ֽ�
	char * pContent = pLen + 2;//char[]

// 	{
// 		for (int i = 0; i < wlen; i++) {
// 			UTF_8ToUnicode(pContent + (i * 3), &wbuf[i]);
// 		}
// 		buf[bufSz - 1] = '\0';
// 	}

	int len = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, pContent, bufSz - dataHeadSz, NULL, NULL);

// 	wchar_t rec[32];
// 	MultiByteToWideChar(CP_UTF8, 0, buf, -1, rec, 32);

	for (int i = 0; i < bufSz; i++) {
		char d = buf[i];
		continue;
	}

	m_client.addMessage(buf, bufSz);
	delete[] buf;
}
