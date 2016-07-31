#pragma once


// CClass 对话框

class CClass : public CDialog
{
	DECLARE_DYNAMIC(CClass)

public:
	CClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClass();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
