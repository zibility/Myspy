// Mess.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "Mess.h"
#include "afxdialogex.h"


// CMess 对话框
HWND g_hPage4 = NULL;

IMPLEMENT_DYNAMIC(CMess, CDialog)

CMess::CMess(CWnd* pParent /*=NULL*/)
	: CDialog(CMess::IDD, pParent)
{

}

CMess::~CMess()
{
}

void CMess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSTATUS, m_listStatus);
}


BEGIN_MESSAGE_MAP(CMess, CDialog)
	ON_LBN_SELCHANGE(IDC_LISTSTATUS, &CMess::OnLbnSelchangeListstatus)
END_MESSAGE_MAP()


// CMess 消息处理程序


BOOL CMess::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_hPage4=m_hWnd;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMess::OnLbnSelchangeListstatus()
{
	// TODO: 在此添加控件通知处理程序代码
	int n=m_listStatus.GetCurSel();
	//获取当前选中的下标
	switch(n)
	{
	case 0:
		if(m_listStatus.GetCheck(0)== 1 )
			::ShowWindow(g_hWnd, SW_SHOW);
		//设置属性 窗口可见
		else
			::ShowWindow(g_hWnd, SW_HIDE);
		//设置属性 窗口隐藏
		break;

	case 1:
		if(m_listStatus.GetCheck(1) == 1)
			::EnableWindow(g_hWnd, TRUE);
		//该函数允许/禁止指定的窗口或控件接受鼠标和键盘的输入
		//ture为允许
		else
			::EnableWindow(g_hWnd,FALSE);
		//false为禁止
		break;
	case 2:
		if(m_listStatus.GetCheck(2) == 1)
			::SetWindowPos(g_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
		//设置属性 总在最前
		else
			::SetWindowPos(g_hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		//设置属性 取消总在最前
		break;
	case 3:
		if(m_listStatus.GetCheck(3) == 1)
			::SendMessage(g_hWnd, EM_SETREADONLY, TRUE, 0);
		//EM_SETREADONLY(&HCF=207),1(0),0 决定是否将编辑控件设为只读，同时决定控件的ES_READONLY风格
		//ture 只读
		else
			::SendMessage(g_hWnd, EM_SETREADONLY, FALSE, 0);
		//false 取消只读
		break;

	case 4:
		if(m_listStatus.GetCheck(4) ==1)
		{
			::ShowWindow(g_hWnd, SW_MAXIMIZE);
			//SW_MAXIMIZE 最大化
			m_listStatus.SetCheck(5,0);
		}
		else
			::ShowWindow (g_hWnd, SW_RESTORE);
		//SW_RESTORE 恢复
		break;
	case 5:

		if (m_listStatus.GetCheck(5) == 1)
		{
			::ShowWindow(g_hWnd, SW_MINIMIZE);
			//SW_MINIMIZE  最小化
			m_listStatus.SetCheck(4,0);
		}
		else
			::ShowWindow(g_hWnd, SW_RESTORE);
		//SW_RESTORE 恢复原来
		break;
	case 6:
		if(m_listStatus.GetCheck(6) ==1)
		{       ::ShowWindow (g_hWnd, SW_RESTORE);
		//SW_RESTORE 恢复原来
		m_listStatus.SetCheck(6,0);
		m_listStatus.SetCheck(5,0);
		m_listStatus.SetCheck(4,0);
		//把最大化 最小化 和还原选项置0
		}
		break;
	case 7:
		if(m_listStatus.GetCheck(7) ==1)
		{
			::SendMessage (g_hWnd, WM_CLOSE, 0, 0);
			//WM_CLOSE 关闭窗口
			m_listStatus.SetCheck(7,0);
		}
		break;
	case 8:
		if(m_listStatus.GetCheck(8) ==1)
		{
			::BringWindowToTop(g_hWnd);
			//该函数将指定的窗口设置到Z序的顶部。
			m_listStatus.SetCheck(8,0);
		}
		break;
	default:
		;
	}

}
