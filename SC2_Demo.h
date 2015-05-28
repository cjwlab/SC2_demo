// SC2_Demo.h : main header file for the SC2_DEMO application
//

#if !defined(AFX_SC2_DEMO_H__77302BF0_6A6C_4F21_A652_780739B661C3__INCLUDED_)
#define AFX_SC2_DEMO_H__77302BF0_6A6C_4F21_A652_780739B661C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSC2_DemoApp:
// See SC2_Demo.cpp for the implementation of this class
//

class CSC2_DemoApp : public CWinApp
{
public:
  CSC2_DemoApp();

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSC2_DemoApp)
  public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL

// Implementation

public:
  //{{AFX_MSG(CSC2_DemoApp)
  afx_msg void OnAppAbout();
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SC2_DEMO_H__77302BF0_6A6C_4F21_A652_780739B661C3__INCLUDED_)
