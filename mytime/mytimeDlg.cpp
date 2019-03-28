
// mytimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mytime.h"
#include "mytimeDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmytimeDlg �Ի���



CmytimeDlg::CmytimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYTIME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmytimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Hour, m_hour);
}

BEGIN_MESSAGE_MAP(CmytimeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CmytimeDlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CmytimeDlg::OnBnClickedButtonPause)
END_MESSAGE_MAP()

void start_time(LPVOID param)
{
	CmytimeDlg *pthis = (CmytimeDlg *)param;
	struct timeb tb;
	struct tm now = { 0 };
	CString  mystr;
	CFont font;
	int hour, min, sec, ms;
	hour = min = sec = ms = 0;
	font.CreatePointFont(200, "΢���ź�");
	pthis->GetDlgItem(IDC_STATIC_Hour)->SetFont(&font);
	pthis->GetDlgItem(IDC_STATIC_MIN)->SetFont(&font);
	pthis->GetDlgItem(IDC_STATIC_SEC)->SetFont(&font);
	pthis->GetDlgItem(IDC_STATIC_MS)->SetFont(&font);
	
	while (pthis->flag)
	{
		ftime(&tb);
		localtime_s(&now, &tb.time);
		if (now.tm_hour != hour)
		{
			hour = now.tm_hour;
			mystr.Format("%02d", hour);
			pthis->GetDlgItem(IDC_STATIC_Hour)->SetWindowText(mystr);
		}
		if (now.tm_min!=min)
		{
			min = now.tm_min;
			mystr.Format("%02d", min);
			pthis->GetDlgItem(IDC_STATIC_MIN)->SetWindowText(mystr);

		}
		if (now.tm_sec!=sec)
		{
			sec = now.tm_sec;
			mystr.Format("%02d", sec);
			pthis->GetDlgItem(IDC_STATIC_SEC)->SetWindowText(mystr);

		}

		mystr.Format("%03d",tb.millitm);
		pthis->GetDlgItem(IDC_STATIC_MS)->SetWindowText(mystr);
		
	}
}
// CmytimeDlg ��Ϣ�������

BOOL CmytimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	flag = true;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_time, this, 0, NULL);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmytimeDlg::OnPaint()
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
HCURSOR CmytimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CmytimeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ((pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) || (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) || (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CmytimeDlg::OnBnClickedCancel()
{

	flag = false;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


HBRUSH CmytimeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

	if (IDC_STATIC_MS == pWnd->GetDlgCtrlID()|| IDC_STATIC_SEC == pWnd->GetDlgCtrlID()|| IDC_STATIC_MIN == pWnd->GetDlgCtrlID()|| IDC_STATIC_Hour == pWnd->GetDlgCtrlID())
	{

			pDC->SetTextColor(RGB(255, 0, 0));	//��ɫ		
			//pDC ->SetBkColor(RGB(0, 255, 255));
	}
	return hbr;
}


void CmytimeDlg::OnBnClickedButtonPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	flag = !flag;
	if (!flag)
	{
		
		GetDlgItem(IDC_BUTTON_Pause)->SetWindowText("�� ʼ");
	}
	else
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_time, this, 0, NULL);
		GetDlgItem(IDC_BUTTON_Pause)->SetWindowText("�� ͣ");

	}
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(TRUE);


}
