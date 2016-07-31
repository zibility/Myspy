// Wind.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "Wind.h"
#include "afxdialogex.h"


// CWind 对话框

HWND g_hPage3=NULL;
IMPLEMENT_DYNAMIC(CWind, CDialog)

CWind::CWind(CWnd* pParent /*=NULL*/)
	: CDialog(CWind::IDD, pParent)
{

}

CWind::~CWind()
{
}

void CWind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWind, CDialog)
END_MESSAGE_MAP()


// CWind 消息处理程序


BOOL CWind::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_hPage3=m_hWnd;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
