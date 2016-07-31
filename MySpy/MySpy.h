
// MySpy.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


#include "mypic.h"
#include "Com.h"
#include "Class.h"
#include "Mess.h"
#include "Style.h"
#include "Wind.h"


extern HWND g_hWnd;
extern HWND g_hMe;
extern HWND g_hPage0;
extern HWND g_hPage1;
extern HWND g_hPage2;
extern HWND g_hPage3;
extern HWND g_hPage4;

extern int g_nHex;
extern CString Display(int nVal);
extern CString getProcPath(int PID);
class CMySpyApp : public CWinApp
{
public:
	CMySpyApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMySpyApp theApp;