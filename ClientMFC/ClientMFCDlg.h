
// ClientMFCDlg.h : ͷ�ļ�
//

#pragma once

#include "MyClient.h"


// CClientMFCDlg �Ի���
class CClientMFCDlg : public CDialogEx
{
// ����
public:
	CClientMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
