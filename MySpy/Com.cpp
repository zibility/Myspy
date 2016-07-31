// Com.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "Com.h"
#include "afxdialogex.h"


#include <stdio.h>
#include <tlhelp32.h>



// CCom 对话框

IMPLEMENT_DYNAMIC(CCom, CDialog)

HWND  g_hPage0;

CCom::CCom(CWnd* pParent /*=NULL*/)
	: CDialog(CCom::IDD, pParent)
{

}

CCom::~CCom()
{
}

void CCom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HWND, m_EditHwnd);
	DDX_Control(pDX, IDC_EDIT_CLASS, m_EditClass);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_EditTitle);
	DDX_Control(pDX, IDC_EDIT_RECT, m_EditRect);
	DDX_Control(pDX, IDC_EDIT_WNDID, m_EditHwndID);
	DDX_Control(pDX, IDC_EDIT_PROCESSID, m_EditProcessID);
	DDX_Control(pDX, IDC_EDIT_PATH, m_EditPath);
}


BEGIN_MESSAGE_MAP(CCom, CDialog)
END_MESSAGE_MAP()


// CCom 消息处理程序


BOOL CCom::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_hPage0=m_hWnd;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString getProcPath(int PID)
{


	HANDLE hProcess=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	//函数通过获取进程信息为指定的进程、进程使用的堆[HEAP]、模块[MODULE]、线程建立一个快照.
	//TH32CS_SNAPPROCESS 需返回的对象			0 为进程ID号
	HANDLE hModule;
	//新建一个句柄
	PROCESSENTRY32* pinfo=new PROCESSENTRY32;
	//新建用来存放快照进程信息的一个结构体
	MODULEENTRY32* minfo=new MODULEENTRY32;
	//这个结构描述了一个条目从一个列表，列举了一个指定的进程所使用的模块
	pinfo->dwSize=sizeof(PROCESSENTRY32);
	minfo->dwSize=sizeof(MODULEENTRY32);
	//设置大小

	char shortpath[MAX_PATH] = "";

	//为路径创建临时变量  MAX_PATH为路径最大长度


	hModule=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,PID);//pinfo->th32ProcessID);
	//函数通过获取进程信息为指定的进程、进程使用的堆[HEAP]、模块[MODULE]、线程建立一个快照.
	//TH32CS_SNAPMODULE 需返回的对象			PID 为进程ID号
	Module32First(hModule, minfo);
	//此函数检索与进程相关联的第一个模块的信息参数 hModule
	// minfo 为 MODULEENTRY32结构的指针。用来返回数据,成功返回ture


	CString str;
	str.Format(L"%s",minfo->szExePath);
	//把路径信息从minfo->szExePath中取出

	CloseHandle(hProcess);
	CloseHandle(hModule);
	//关闭句柄
	if(pinfo) delete pinfo;
	if(minfo) delete minfo;
	//删除句柄

	return str;
	//返回句柄
}
