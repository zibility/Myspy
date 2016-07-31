#pragma once
#include "afxwin.h"


// CMess 对话框

class CMess : public CDialog
{
	DECLARE_DYNAMIC(CMess)

public:
	CMess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMess();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox m_listStatus;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListstatus();
};
