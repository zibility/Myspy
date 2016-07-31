#pragma once


// CMyPic

class CMyPic : public CStatic
{
	DECLARE_DYNAMIC(CMyPic)

public:
	CMyPic();
	virtual ~CMyPic();

	
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CStatic m_mypic;
};


