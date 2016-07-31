// Style.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "Style.h"
#include "afxdialogex.h"


// CStyle 对话框

HWND g_hPage1=NULL;

IMPLEMENT_DYNAMIC(CStyle, CDialog)

CStyle::CStyle(CWnd* pParent /*=NULL*/)
	: CDialog(CStyle::IDD, pParent)
{

}

CStyle::~CStyle()
{
}

void CStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStyle, CDialog)
END_MESSAGE_MAP()


// CStyle 消息处理程序


BOOL CStyle::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	g_hPage1=m_hWnd;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
