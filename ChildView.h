// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__104728A1_3324_4E43_A72E_71A9CC3EF26F__INCLUDED_)
#define AFX_CHILDVIEW_H__104728A1_3324_4E43_A72E_71A9CC3EF26F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
  CChildView();

// Attributes
public:

// Operations
public:
   void SetBmp(HBITMAP hbm, int ixres, int iyres);
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CChildView)
  protected:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CChildView();

  // Generated message map functions
protected:

  HBITMAP m_hBitmap;
  int m_iXRes, m_iYRes;
  //{{AFX_MSG(CChildView)
  afx_msg void OnPaint();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__104728A1_3324_4E43_A72E_71A9CC3EF26F__INCLUDED_)
