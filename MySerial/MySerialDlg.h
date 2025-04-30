
// MySerialDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "SimpleSerial.h"


// CMySerialDlg ��ȭ ����
class CMySerialDlg : public CDialogEx
{
	CSimpleSerial *m_pSerial;

// �����Դϴ�.
public:
	CMySerialDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CMySerialDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSERIAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	void DispSerialStatus();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT wmSerialReceived(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editMsgList;
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedCheckConnect();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
