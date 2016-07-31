// Class.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "Class.h"
#include "afxdialogex.h"


// CClass 对话框
HWND g_hPage2=NULL;
IMPLEMENT_DYNAMIC(CClass, CDialog)

CClass::CClass(CWnd* pParent /*=NULL*/)
	: CDialog(CClass::IDD, pParent)
{

}

CClass::~CClass()
{
}

void CClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClass, CDialog)
END_MESSAGE_MAP()


// CClass 消息处理程序


BOOL CClass::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化


	g_hPage2=m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
