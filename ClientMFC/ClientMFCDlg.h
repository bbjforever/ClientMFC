
// ClientMFCDlg.h : 头文件
//

#pragma once

#include "MyClient.h"


// CClientMFCDlg 对话框
class CClientMFCDlg : public CDialogEx
{
// 构造
public:
	CClientMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnSend();
//	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedSend();

private:
	CMyClient m_client;
};
