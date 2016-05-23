
// ClientMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientMFC.h"
#include "ClientMFCDlg.h"
#include "afxdialogex.h"
#include "MsgWrite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientMFCDlg 对话框



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


// CClientMFCDlg 消息处理程序

BOOL CClientMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	if (m_client.createClient()) {
		m_client.start();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
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

	CStringW strWide = CT2CW(str); // 将T字符转换成宽字符
	WCHAR * wbuf = strWide.GetBuffer(); // 获取CString内部缓存
	int wlen = strWide.GetLength();

	int bufSz = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, NULL, 0, NULL, NULL);// wlen * 3 + 1;
	int sLen = bufSz - 1;//转换成的char的长度
	int dataHeadSz = 3;/* char + short */
	bufSz += dataHeadSz;
	char * buf = new char[bufSz];
	ZeroMemory(buf, bufSz * sizeof(char));
	char * pType = buf;//char
	*pType = 1;
	char * pLen = pType + 1;//short
	*pLen = sLen >> 8;//高字节
	*(pLen + 1) = sLen;//低字节
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
