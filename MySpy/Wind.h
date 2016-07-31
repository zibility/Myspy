#pragma once


// CWind 对话框

class CWind : public CDialog
{
	DECLARE_DYNAMIC(CWind)

public:
	CWind(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWind();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
