
// mytimeDlg.h : ͷ�ļ�
//

#include <time.h>      //���ͷ�ļ�
#include <sys/timeb.h>
#include "afxwin.h"
using namespace std;

#pragma once


// CmytimeDlg �Ի���
class CmytimeDlg : public CDialogEx
{
// ����
public:
	CmytimeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTIME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
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
