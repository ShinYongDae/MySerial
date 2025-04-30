
// MySerialDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MySerial.h"
#include "MySerialDlg.h"
#include "afxdialogex.h"

#include "SimpleSerial.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySerialDlg ��ȭ ����



CMySerialDlg::CMySerialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYSERIAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSerial = NULL;
}

CMySerialDlg::~CMySerialDlg()
{
	if (m_pSerial)
	{
		delete m_pSerial;
		m_pSerial = NULL;
	}
}

void CMySerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MESSAGE_LIST, m_editMsgList);
}

BEGIN_MESSAGE_MAP(CMySerialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SERIAL_RECEIVED, wmSerialReceived)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CMySerialDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_CHECK_CONNECT, &CMySerialDlg::OnBnClickedCheckConnect)
	ON_BN_CLICKED(IDC_BTN_SEND, &CMySerialDlg::OnBnClickedBtnSend)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMySerialDlg �޽��� ó����

BOOL CMySerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString sComPort = _T("3"), sBaudRate = _T("9600"), sDataSize = _T("8");

	GetDlgItem(IDC_EDIT_COM_PORT)->SetWindowText(sComPort);
	GetDlgItem(IDC_EDIT_BAUD_RATE)->SetWindowText(sBaudRate);
	GetDlgItem(IDC_EDIT_DATA_SIZE)->SetWindowText(sDataSize);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMySerialDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMySerialDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMySerialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CMySerialDlg::wmSerialReceived(WPARAM wParam, LPARAM lParam)
{
	CString sReceived = (LPCTSTR)lParam;

	CString sDisp;
	GetDlgItem(IDC_MESSAGE_LIST)->GetWindowText(sDisp);
	sDisp += sReceived + _T("\r\n");
	GetDlgItem(IDC_MESSAGE_LIST)->SetWindowText(sDisp);

	return (LRESULT)1;
}


void CMySerialDlg::OnBnClickedBtnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (::IsWindow(m_editMsgList.GetSafeHwnd()))
	{
		int nLen = m_editMsgList.GetWindowTextLength();
		m_editMsgList.SetSel(0, -1);
		m_editMsgList.Clear();
	}
}


void CMySerialDlg::OnBnClickedCheckConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sComPort, sBaudRate, sDataSize;
	BOOL bOn = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();

	if (bOn)
	{
		GetDlgItem(IDC_EDIT_COM_PORT)->GetWindowText(sComPort);
		GetDlgItem(IDC_EDIT_BAUD_RATE)->GetWindowText(sBaudRate);
		GetDlgItem(IDC_EDIT_DATA_SIZE)->GetWindowText(sDataSize);

		if (!m_pSerial)
			m_pSerial = new CSimpleSerial(this, (BYTE)_tstoi(sComPort), (DWORD)_tstoi(sBaudRate), (BYTE)_tstoi(sDataSize));
	}
	else
	{
		if (m_pSerial)
		{
			delete m_pSerial;
			m_pSerial = NULL;
		}
	}
}


void CMySerialDlg::OnBnClickedBtnSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sMsg;
	GetDlgItem(IDC_TXT_MESSAGE)->GetWindowText(sMsg);
	if (!sMsg.IsEmpty())
	{
		if (m_pSerial)
		{
			m_pSerial->Send(sMsg);
		}
	}
}


void CMySerialDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		DispSerialStatus();
		SetTimer(0, 300, NULL);
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMySerialDlg::DispSerialStatus()
{
	if (m_pSerial)
	{
		BOOL bOn = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
		if (m_pSerial->IsConnected())
		{
			if (!bOn)
				((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->SetCheck(TRUE);
		}
		else
		{
			if (bOn)
				((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->SetCheck(FALSE);
		}
	}
}