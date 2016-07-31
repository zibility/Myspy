
// MySpyDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Com.h"
#include "Style.h"
#include "Class.h"
#include "Wind.h"
#include "Mess.h"
#include "MyPic.h"



// CMySpyDlg 对话框
class CMySpyDlg : public CDialogEx
{
// 构造
public:
	CMySpyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSPY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl    m_Tab;
	CMyPic      m_Pic;

	CCom   m_page0;
	CStyle m_page1;
	CClass m_page2;
	CWind  m_page3;
	CMess  m_page4;

	BOOL    InitTabDialog();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckTop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheck16();
};
