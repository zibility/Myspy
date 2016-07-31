#pragma once


// CStyle 对话框

class CStyle : public CDialog
{
	DECLARE_DYNAMIC(CStyle)

public:
	CStyle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStyle();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
