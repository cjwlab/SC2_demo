// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "SC2_Demo.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
  m_hBitmap = NULL;
  m_iXRes = 0;
  m_iYRes = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
  //{{AFX_MSG_MAP(CChildView)
  ON_WM_PAINT()
  ON_WM_ERASEBKGND()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
  if (!CWnd::PreCreateWindow(cs))
    return FALSE;
  
  cs.dwExStyle |= WS_EX_CLIENTEDGE;
  cs.style &= ~WS_BORDER;
  cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, 
    ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1), NULL);
  
  return TRUE;
}

void CChildView::OnPaint() 
{
  CPaintDC dc(this); // device context for painting
  CDC memdc;
  CRect rect;
  HBITMAP oldbmp;
  
  static int illi = 0;
  
  GetClientRect(&rect);
  if (m_hBitmap == NULL)
  {
    CString csh;

    dc.PatBlt(0, 0, rect.right, rect.bottom, WHITENESS);

    csh = "If the open camera command failed, you might create the file 'sc2_cam.log' inside the bin directory.\r\n";
    csh += "This enables the logging to find out the error after the next start, by reading the logfile entries (see pco_err.h).";
    csh += "\r\n\r\n1. Start Record\r\n2. Stop Record\r\n3. Play!";
    dc.DrawText((LPCTSTR)csh, csh.GetLength(), rect, DT_LEFT);

  }
  else
  {
    dc.SetStretchBltMode(COLORONCOLOR);// HALFTONE
    memdc.CreateCompatibleDC(&dc);
    SetBrushOrgEx(memdc.GetSafeHdc(), 0, 0, NULL);
    oldbmp = (HBITMAP) memdc.SelectObject(m_hBitmap);  // We want to use the bitmap for the memory DC
    dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, m_iXRes, m_iYRes, SRCCOPY);
    
    memdc.SelectObject(oldbmp);
  }
}

void CChildView::SetBmp(HBITMAP hbm, int ixres, int iyres)
{
  if (hbm != NULL)
    m_hBitmap = hbm;
  else
    m_hBitmap = NULL;
  m_iXRes = ixres;
  m_iYRes = iyres;
  Invalidate(TRUE);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
  return TRUE;
}
