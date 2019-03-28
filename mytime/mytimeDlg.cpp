
// mytimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mytime.h"
#include "mytimeDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmytimeDlg 对话框



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
	font.CreatePointFont(200, "微软雅黑");
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
// CmytimeDlg 消息处理程序

BOOL CmytimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	flag = true;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_time, this, 0, NULL);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmytimeDlg::OnPaint()
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
HCURSOR CmytimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CmytimeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) || (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) || (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CmytimeDlg::OnBnClickedCancel()
{

	flag = false;
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


HBRUSH CmytimeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (IDC_STATIC_MS == pWnd->GetDlgCtrlID()|| IDC_STATIC_SEC == pWnd->GetDlgCtrlID()|| IDC_STATIC_MIN == pWnd->GetDlgCtrlID()|| IDC_STATIC_Hour == pWnd->GetDlgCtrlID())
	{

			pDC->SetTextColor(RGB(255, 0, 0));	//红色		
			//pDC ->SetBkColor(RGB(0, 255, 255));
	}
	return hbr;
}


void CmytimeDlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	flag = !flag;
	if (!flag)
	{
		
		GetDlgItem(IDC_BUTTON_Pause)->SetWindowText("开 始");
	}
	else
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_time, this, 0, NULL);
		GetDlgItem(IDC_BUTTON_Pause)->SetWindowText("暂 停");

	}
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(TRUE);


}
