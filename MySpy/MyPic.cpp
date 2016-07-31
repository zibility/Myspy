// MyPic.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "MyPic.h"


// CMyPic
extern HWND g_hWnd;

IMPLEMENT_DYNAMIC(CMyPic, CStatic)

CMyPic::CMyPic()
{

}

CMyPic::~CMyPic()
{
}


BEGIN_MESSAGE_MAP(CMyPic, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



void CMyPic::OnLButtonDown(UINT nFlags, CPoint point) 
{

	SetCapture();//该函数在属于当前线程的指定窗口里设置鼠标捕获。一旦窗口捕获了鼠标，所有鼠标输入都针对该窗口，无论光标是否在窗口的边界内。

	HCURSOR hc=LoadCursor(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR1));              //加载光标1

	::SetCursor(hc);                                                                            //设置  光标

	HICON hicon2=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON2));                 //加载位图

	this->SetIcon(hicon2);                                                                      //函数用于设置按钮的图标。
	
	FromHandle(g_hMe)->SetTimer(1,600,NULL);

	CStatic::OnLButtonDown(nFlags, point);
	
}

// CMyPic 消息处理程序



void CMyPic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	//该函数从当前线程中的窗口释放鼠标捕获，并恢复通常的鼠标输入处理。
	HICON hicon1=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON1));

	this->SetIcon(hicon1);

	//找到鼠标当前窗口的句柄
	POINT pt;
	::GetCursorPos(&pt);
	g_hWnd=::WindowFromPoint(pt);

	HWND grayHwnd = ::GetWindow(g_hWnd, GW_CHILD);
	RECT tempRc;
	BOOL bFind=FALSE;
	while (grayHwnd)
	{
		::GetWindowRect(grayHwnd, &tempRc);
		if(::PtInRect(&tempRc,pt))
		{
			bFind = TRUE;
			break;
		}
		else
			grayHwnd = ::GetWindow(grayHwnd, GW_HWNDNEXT);

	}//while
	if(bFind == TRUE)
	{
		bFind= FALSE;
		g_hWnd = grayHwnd;
	}
	else

		;//Wnd=UnHwnd

	((CCom*)FromHandle(g_hPage0))->m_EditHwnd.SetWindowText(Display((int)g_hWnd));       //  FromHandle     根据  窗口句柄  得到  窗口类       

	//GetClassName    根据窗口句柄    获得  窗口类   
	  WCHAR wzClass[200]=L"\0";
	::GetClassName(g_hWnd,wzClass,200);                                    
	((CCom*)FromHandle(g_hPage0))->m_EditClass.SetWindowText(wzClass);


	
	//GetWindowText   根据窗口句柄   得到  窗口标题   把标题文本添加到相关edit控件中
	 WCHAR wzTitle[200]=L"\0";
	::GetWindowText(g_hWnd,wzTitle,200);
	((CCom*)FromHandle(g_hPage0))->m_EditTitle.SetWindowText(wzTitle);

	//GetWindowLong   该函数获得指定窗口的有关信息，函数也获得在额外窗口内存中指定偏移位地址的32位度整型值。    根据传参的  不同   获得不同信息   
	long iWNDID=GetWindowLong(g_hWnd,GWL_ID);
	((CCom*)FromHandle(g_hPage0))->m_EditHwndID.SetWindowText(Display((int)iWNDID));
	

	//GetWindowThreadProcessId    根据窗口句柄   获得进程ID 
	unsigned long iPID=0;
	GetWindowThreadProcessId(g_hWnd,&iPID);
	((CCom*)FromHandle(g_hPage0))->m_EditProcessID.SetWindowText(Display((int)iPID));
	//把进程ID添加到相关edit控件中


	//getProcPath   根据进程   ID  获得进程路径 
	CString strPath;
	strPath = getProcPath(iPID);
	((CCom*)FromHandle(g_hPage0))->m_EditPath.SetWindowText(strPath);


	//获得窗口矩形     获得窗口区域  
	RECT rc;
	::GetWindowRect(g_hWnd, &rc);      
	CString strRect;
	strRect.Format(L"(%d,%d),(%d,%d) %dx%d",rc.left,rc.top,rc.right,rc.bottom,
		rc.right-rc.left,rc.bottom-rc.top);
	((CCom*)FromHandle(g_hPage0))->m_EditRect.SetWindowText(strRect);


	FromHandle(g_hMe)->KillTimer(1);    //销毁ONTIMER




	

	CListBox* pListStyle=(CListBox*)(((CStyle*)FromHandle(g_hPage1))->GetDlgItem(IDC_LIST_STYLE));
	CListBox* pListExStyle=(CListBox*)(((CStyle*)FromHandle(g_hPage1))->GetDlgItem(IDC_LIST_EX_STYLE));

	CEdit* pEditStyle=(CEdit*)(((CStyle*)FromHandle(g_hPage1))->GetDlgItem(IDC_EDIT_STYLE));
	CEdit* pEditExStyle=(CEdit*)(((CStyle*)FromHandle(g_hPage1))->GetDlgItem(IDC_EDIT_EX_STYLE));

	long   style = GetWindowLong(g_hWnd, GWL_STYLE);
	long  styleEx= GetWindowLong(g_hWnd, GWL_EXSTYLE);

	pEditStyle->SetWindowText(Display((int)style));
	pEditExStyle->SetWindowText(Display((int)styleEx));

	pListStyle->ResetContent();       //?????
	pListExStyle->ResetContent();     


	
	CCheckListBox* pListStatus=(CCheckListBox*)(((CMess*)FromHandle(g_hPage4))->GetDlgItem(IDC_LISTSTATUS));
	for(int i=0;i<9;i++)
		pListStatus->SetCheck(i,0);      


	if (style & WS_BORDER)
		pListStyle->AddString(L"WS_BORDER");

	if( style & WS_CAPTION)
		pListStyle->AddString(L"WS_CAPTION");

	if( style & WS_CHILD)
		pListStyle->AddString(L"WS_CHILD");

	if( style & WS_CLIPCHILDREN )
		pListStyle->AddString(L"WS_CLIPCHILDREN");

	if( style & WS_CLIPSIBLINGS )
		pListStyle->AddString(L"WS_CLIPSIBLINGS");

	if( style & WS_DISABLED )
		pListStyle->AddString(L"WS_DISABLED");
	else  
		pListStatus->SetCheck(1,1);

	if(style & WS_DLGFRAME)
		pListStyle->AddString(L"WS_DLGFRAME");

	if( style & WS_GROUP)
		pListStyle->AddString(L"WS_GROUP");

	if( style &WS_HSCROLL )
		pListStyle->AddString(L"WS_HSCROLL");

	if( style&  WS_MAXIMIZE )
	{pListStyle->AddString(L"WS_MAXIMIZE");

	pListStatus->SetCheck(4,1);
	}

	if( style&  WS_MAXIMIZEBOX)
		pListStyle->AddString( L"WS_MAXIMIZEBOX");

	if( style&  WS_MINIMIZE )
	{
		pListStyle->AddString(L"WS_MINIMIZE");
		pListStatus->SetCheck(5,1);
	} 

	if( style & WS_MINIMIZEBOX)
		pListStyle->AddString(L"WS_MINIMIZEBOX");

	if( style&  WS_POPUP)
		pListStyle->AddString(L"WS_POPUP");

	if( style& WS_SYSMENU )
		pListStyle->AddString(L"WS_SYSMENU");

	if( style& WS_TABSTOP)
		pListStyle->AddString(L"WS_TABSTOP");

	if( style&  WS_THICKFRAME)
		pListStyle->AddString(L"WS_THICKFRAME");

	if( style& WS_VISIBLE )
	{pListStyle->AddString(L"WS_VISIBLE");
	pListStatus->SetCheck(0,1);
	}

	if( style&  WS_VSCROLL )
		pListStyle->AddString(L"WS_VSCROLL");

	if( style&  ES_READONLY )
	{pListStyle->AddString(L"ES_READONLY");
	pListStatus->SetCheck(3,1);
	}


	if( styleEx &  WS_EX_ACCEPTFILES )
		pListExStyle->AddString(L"WS_EX_ACCEPTFILES");
	if( styleEx &  WS_EX_DLGMODALFRAME )
		pListExStyle->AddString(L"WS_EX_DLGMODALFRAME");

	if( styleEx &  WS_EX_NOPARENTNOTIFY )
		pListExStyle->AddString(L"WS_EX_NOPARENTNOTIFY");
	if( styleEx &  WS_EX_TOPMOST )
	{
		pListExStyle->AddString(L"WS_EX_TOPMOST");
		pListStatus->SetCheck(2,1);
	}


	if( styleEx &  WS_EX_TRANSPARENT )
		pListExStyle->AddString(L"WS_EX_TRANSPARENT");

	if( styleEx &  WS_EX_MDICHILD )
		pListExStyle->AddString(L"WS_EX_MDICHILD");

	if( styleEx &  WS_EX_TOOLWINDOW )
		pListExStyle->AddString(L"WS_EX_TOOLWINDOW");

	if( styleEx &  WS_EX_WINDOWEDGE )
		pListExStyle->AddString(L"WS_EX_WINDOWEDGE");

	if( styleEx &  WS_EX_CLIENTEDGE )
		pListExStyle->AddString(L"WS_EX_CLIENTEDGE");

	if( styleEx &  WS_EX_CONTEXTHELP )
		pListExStyle->AddString(L"WS_EX_CONTEXTHELP");

	if( styleEx &  WS_EX_RIGHT )
		pListExStyle->AddString(L"WS_EX_RIGHT");
	if( styleEx &  WS_EX_RTLREADING )
		pListExStyle->AddString(L"WS_EX_RTLREADING");

	if( styleEx &  WS_EX_LEFTSCROLLBAR )
		pListExStyle->AddString(L"WS_EX_LEFTSCROLLBAR");

	if( styleEx &  WS_EX_CONTROLPARENT )
		pListExStyle->AddString(L"WS_EX_CONTROLPARENT");

	if( styleEx &  WS_EX_STATICEDGE )
		pListExStyle->AddString(L"WS_EX_STATICEDGE");

	if( styleEx &  WS_EX_APPWINDOW )
		pListExStyle->AddString(L"WS_EX_APPWINDOW");

	
	//获得  类
	int classstyle = GetClassLong(g_hWnd, GCL_STYLE);

	(FromHandle(g_hPage2))->SetDlgItemText(IDC_EDIT_CALSSVALUE,Display(classstyle));    //类  值
                              
	((CClass*)FromHandle(g_hPage2))->SetDlgItemText(IDC_EDIT_CLASSNAME,wzClass);
	


	CListBox* pListClass=(CListBox*)(FromHandle(g_hPage2)->GetDlgItem(IDC_LIST_CLASS));
	//获得类样式的ListBox控件的句柄
	pListClass->ResetContent();
	//清空上次的List


	if(classstyle &  CS_BYTEALIGNCLIENT )
		pListClass->AddString(L"CS_BYTEALIGNCLIENT");

	if(classstyle &  CS_BYTEALIGNWINDOW )
		pListClass->AddString(L"CS_BYTEALIGNWINDOW");

	if(classstyle &  CS_CLASSDC )
		pListClass->AddString(L"CS_CLASSDC");

	if(classstyle &  CS_DBLCLKS )
		pListClass->AddString(L"CS_DBLCLKS");

	// Was CS_GLOBALCLASS (has same value)
	if(classstyle & CS_GLOBALCLASS)  
		pListClass->AddString(L"CS_GLOBALCLASS");//PUBLICCLASS )

	if(classstyle &  CS_HREDRAW )
		pListClass->AddString(L"CS_HREDRAW");

	if(classstyle &  CS_NOCLOSE )
		pListClass->AddString(L"CS_NOCLOSE");

	if(classstyle &  CS_OWNDC )
		pListClass->AddString(L"CS_OWNDC");

	if(classstyle &  CS_PARENTDC )
		pListClass->AddString(L"CS_PARENTDC");

	if(classstyle &  CS_SAVEBITS )
		pListClass->AddString(L"CS_SAVEBITS");

	if(classstyle &  CS_VREDRAW )
		pListClass->AddString(L"CS_VREDRAW");






	CWind* pPage3=(CWind*)FromHandle(g_hPage3);

	HWND tempHandle;
	WCHAR tempstr[255]=L"\0";
	tempHandle = g_hWnd;   //本窗口句柄
	pPage3->SetDlgItemText(IDC_MYHWND, Display((int)tempHandle));

	//获取本窗口标题
	::SendMessage(tempHandle, WM_GETTEXT, 255, (LPARAM)tempstr);

	pPage3->SetDlgItemText(IDC_MYTITLE, tempstr);

	tempHandle = ::GetNextWindow(g_hWnd, GW_HWNDPREV); 

	pPage3->SetDlgItemText(IDC_PREHWND, Display((int)tempHandle));


	memset(tempstr,0,255);

	::SendMessage(tempHandle, WM_GETTEXT, 255, (LPARAM)tempstr);
	pPage3->SetDlgItemText(IDC_PRETITLE, tempstr);

	tempHandle = ::GetNextWindow(g_hWnd, GW_HWNDNEXT);   //下一窗口
	//GW_HWNDPREV  后一个窗口句柄
	pPage3->SetDlgItemText(IDC_NEXTHWND,Display((int)tempHandle));

	memset(tempstr,0,255);   //获取下一窗口标题并添加
	::SendMessage(tempHandle, WM_GETTEXT, 255, (LPARAM)tempstr);
	pPage3->SetDlgItemText(IDC_NEXTTITLE, tempstr);

	tempHandle = ::GetParent(g_hWnd);   
	pPage3->SetDlgItemText(IDC_PARENTHWND, Display((int)tempHandle));
	memset(tempstr,0,255);
	::SendMessage(tempHandle, WM_GETTEXT, 255, (LPARAM)tempstr);
	pPage3->SetDlgItemText(IDC_PARENTTITLE,tempstr);

	tempHandle = ::GetWindow(g_hWnd, GW_CHILD);        
	//第一子窗口
	pPage3->SetDlgItemText(IDC_CHILDHWND,Display((int)tempHandle));
	memset(tempstr,-0,255);
	::SendMessage(tempHandle, WM_GETTEXT, 255, (LPARAM)tempstr);
	pPage3->SetDlgItemText(IDC_CHILDTITLE,tempstr);

	tempHandle = ::GetWindow(g_hWnd, GW_OWNER);     
	//GW_OWNER 所有者窗口
	pPage3->SetDlgItemText(IDC_OWNERHWND,Display((int)tempHandle));
	memset(tempstr,0,255);
	::SendMessage(tempHandle, WM_GETTEXT, 255, (LPARAM)tempstr);
	pPage3->SetDlgItemText(IDC_OWNERTITLE, tempstr);

	CStatic::OnLButtonUp(nFlags, point);
}
