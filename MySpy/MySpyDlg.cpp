
// MySpyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySpy.h"
#include "MySpyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

HWND g_hWnd=(HWND)123;
HWND g_hMe;
int  g_nHex=1;   //  标志  16进制  是否被选中


CString Display(int nVal)
{
	CString str;
	if(g_nHex==1)		
	{
		str.Format(L"%x",nVal);
		str.MakeUpper();
		
	}
	else
		str.Format(L"%d",nVal);

	return str;
}


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySpyDlg 对话框




CMySpyDlg::CMySpyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySpyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);



}

void CMySpyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}

BEGIN_MESSAGE_MAP(CMySpyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CMySpyDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_CHECK_TOP, &CMySpyDlg::OnBnClickedCheckTop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_16, &CMySpyDlg::OnBnClickedCheck16)
END_MESSAGE_MAP()


// CMySpyDlg 消息处理程序

BOOL CMySpyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CButton*)GetDlgItem(IDC_CHECK_TOP))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_16))->SetCheck(1);

	if(::SetWindowPos(m_hWnd,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE))      //   一开始就把窗口置于最前  
		TRACE("置于最前失败");

	//关键函数
	m_Pic.SubclassDlgItem(IDC_PIC,this);
	g_hMe=m_hWnd;

	InitTabDialog();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMySpyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMySpyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMySpyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CMySpyDlg::InitTabDialog()
{

	m_Tab.InsertItem(0,L"常规");
	m_Tab.InsertItem(1,L"样式");
	m_Tab.InsertItem(2,L"类");
	m_Tab.InsertItem(3,L"窗口");
	m_Tab.InsertItem(4,L"消息");

	m_page0.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB));
	m_page1.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB));
	m_page2.Create(IDD_DIALOG3,GetDlgItem(IDC_TAB));
	m_page3.Create(IDD_DIALOG4,GetDlgItem(IDC_TAB));
	m_page4.Create(IDD_DIALOG5,GetDlgItem(IDC_TAB));

	CRect rc;
	m_Tab.GetClientRect(rc);
	rc.top +=23;
	rc.bottom -= 3;
	rc.left += 3;
	rc.right -= 3;

	m_page0.MoveWindow(rc);
	m_page1.MoveWindow(rc);
	m_page2.MoveWindow(rc);
	m_page3.MoveWindow(rc);
	m_page4.MoveWindow(rc);

    m_page0.ShowWindow(SW_SHOW);	
	m_Tab.SetCurSel(0);
	g_hMe=m_hWnd;

	
	CCheckListBox* plistStatus=((CCheckListBox*)FromHandle(g_hPage4)->GetDlgItem(IDC_LISTSTATUS));
	plistStatus->AddString(L"窗口可见");
	plistStatus->AddString(L"窗口可用");
	plistStatus->AddString(L"总在最前");
	plistStatus->AddString(L"窗口只读");	
	plistStatus->AddString(L"最大化");
	plistStatus->AddString(L"最小化");
	plistStatus->AddString(L"窗口还原");
	plistStatus->AddString(L"关闭窗口");
	plistStatus->AddString(L"激活窗口");


	return TRUE;

}

void CMySpyDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{

	int i=m_Tab.GetCurSel();



	//根据当前所选的下标来显示所需窗口
	switch(i) {
	case 0:
		m_page0.ShowWindow(SW_SHOW);
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_page0.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_SHOW);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_page0.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_SHOW);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_page0.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_SHOW);
		m_page4.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_page0.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_SHOW);
		break;
	default:
		;
	}
}


void CMySpyDlg::OnBnClickedCheckTop()
{
	// TODO: Add your control notification handler code here
	int nTop=((CButton*)GetDlgItem(IDC_CHECK_TOP))->GetCheck();
	//得到控件数据    选中为1  
	if(nTop==1)
		::SetWindowPos(m_hWnd,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	else
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
}



void CMySpyDlg::OnBnClickedCheck16()
{
	// TODO: 在此添加控件通知处理程序代码

	g_nHex=((CButton*)GetDlgItem(IDC_CHECK_16))->GetCheck();
}


void CMySpyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	POINT pnt;
	RECT rc;


	HWND DeskHwnd = ::GetDesktopWindow();   //该函数返回桌面窗口的句柄。桌面窗口覆盖整个屏幕。桌面窗口是一个要在其上绘制所有的图标和其他窗口的区域。
	HDC DeskDC = ::GetWindowDC(DeskHwnd);     //获得的设备环境覆盖了整个窗口    


	int oldRop2 = SetROP2(DeskDC, 10);       //回复系统默认色彩模式      ???   没有这一句  整个窗口  重绘白色？

	::GetCursorPos(&pnt);                    //得到当前鼠标位置   
	HWND UnHwnd = ::WindowFromPoint(pnt) ;   //该函数获得包含指定点的窗口的句柄    

	g_hWnd=UnHwnd;                             
	HWND grayHwnd = ::GetWindow(g_hWnd, GW_CHILD);     //该函数返回与指定窗口有特定关系（如Z序或所有者）的窗口句柄。    GW_CHILD(&H5)：如果指定窗口是父窗口，则获得的是在Tab序顶端的子窗口的句柄，否则为NULL。
														//函数仅检查指定父窗口的子窗口，不检查继承窗口。

	RECT tempRc;
	BOOL bFind=FALSE;
	//找到标记
	while (grayHwnd)
	{
		::GetWindowRect(grayHwnd, &tempRc);

		if(::PtInRect(&tempRc,pnt))//判断点pnt是否在RECT对象tempRc 如果在，则返回非零
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

	::GetWindowRect(g_hWnd, &rc);      
	//'获得窗口矩形的尺寸

	if( rc.left < 0 ) rc.left = 0;
	if (rc.top < 0 ) rc.top = 0;
	//判断窗口超出屏幕的问题

	HPEN newPen = ::CreatePen(0, 3, RGB(125,0,125));    
	HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);
	::Rectangle(DeskDC, rc.left, rc.top, rc.right, rc.bottom);  

	Sleep(400);   
	::Rectangle( DeskDC, rc.left, rc.top, rc.right, rc.bottom);

	::SetROP2(DeskDC, oldRop2);
	::SelectObject( DeskDC, oldPen);
	::DeleteObject(newPen);
	::ReleaseDC( DeskHwnd, DeskDC);

	DeskDC = NULL;

	CDialogEx::OnTimer(nIDEvent);
}

