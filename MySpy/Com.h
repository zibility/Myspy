#pragma once
#include "afxwin.h"


// CCom 对话框

class CCom : public CDialog
{
	DECLARE_DYNAMIC(CCom)

public:
	CCom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCom();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditHwnd;
	CEdit m_EditClass;
	CEdit m_EditTitle;
	CEdit m_EditRect;
	CEdit m_EditHwndID;
	CEdit m_EditProcessID;
	CEdit m_EditPath;
	virtual BOOL OnInitDialog();
};
