
// mytimeDlg.h : 头文件
//

#include <time.h>      //添加头文件
#include <sys/timeb.h>
#include "afxwin.h"
using namespace std;

#pragma once


// CmytimeDlg 对话框
class CmytimeDlg : public CDialogEx
{
// 构造
public:
	CmytimeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTIME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString str;
	bool flag = false;
	afx_msg void OnBnClickedCancel();
	CStatic m_hour;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonPause();
};
