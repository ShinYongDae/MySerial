
// MySerialDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "SimpleSerial.h"


// CMySerialDlg 대화 상자
class CMySerialDlg : public CDialogEx
{
	CSimpleSerial *m_pSerial;

// 생성입니다.
public:
	CMySerialDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CMySerialDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSERIAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	void DispSerialStatus();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
