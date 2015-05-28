// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D69DF21D_25EB_49E4_ADD2_0DE842D3170B__INCLUDED_)
#define AFX_MAINFRM_H__D69DF21D_25EB_49E4_ADD2_0DE842D3170B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"
#include "SC2_Class.h"

class CMainFrame : public CFrameWnd
{
  
public:
  CMainFrame();
protected: 
  DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMainFrame)
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual       ~CMainFrame();
#ifdef _DEBUG
  virtual void  AssertValid() const;
  virtual void  Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
  CStatusBar    m_wndStatusBar;
  CToolBar      m_wndToolBar;
  CReBar        m_wndReBar;
  CChildView    m_wndView;

  CSC2Class     *m_Camera;
  bool          m_bRecord,
                m_bPlay;

// Generated message map functions
protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSetFocus(CWnd *pOldWnd);
  afx_msg void OnStartRecord();
  afx_msg void OnUpdateStartRecord(CCmdUI* pCmdUI);
  afx_msg void OnStartPlay();
  afx_msg void OnUpdateStartPlay(CCmdUI* pCmdUI);
  afx_msg void OnStopCamera();
  afx_msg LRESULT OnNextImage(WPARAM, LPARAM);
  afx_msg LRESULT OnThreadError(WPARAM, LPARAM);
  afx_msg void OnAutominmax();
  afx_msg void OnViewConvertdlg();
  afx_msg void OnUpdateViewConvertdlg(CCmdUI* pCmdUI);
  afx_msg void OnViewCameradlg();
  afx_msg void OnUpdateViewCameradlg(CCmdUI* pCmdUI);
  afx_msg LRESULT OnConvertDialog(WPARAM, LPARAM);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D69DF21D_25EB_49E4_ADD2_0DE842D3170B__INCLUDED_)
