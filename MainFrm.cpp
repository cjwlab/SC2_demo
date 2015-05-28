// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SC2_Demo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CREATE()
  ON_WM_SETFOCUS()
  ON_COMMAND(ID_START_RECORD, OnStartRecord)
  ON_UPDATE_COMMAND_UI(ID_START_RECORD, OnUpdateStartRecord)
  ON_COMMAND(ID_START_PLAY, OnStartPlay)
  ON_UPDATE_COMMAND_UI(ID_START_PLAY, OnUpdateStartPlay)
  ON_COMMAND(ID_STOP_CAMERA, OnStopCamera)
  ON_COMMAND(ID_AUTOMINMAX, OnAutominmax)
  ON_COMMAND(ID_VIEW_CONVERTDLG, OnViewConvertdlg)
  ON_UPDATE_COMMAND_UI(ID_VIEW_CONVERTDLG, OnUpdateViewConvertdlg)
  ON_COMMAND(ID_VIEW_CAMERADLG, OnViewCameradlg)
  ON_UPDATE_COMMAND_UI(ID_VIEW_CAMERADLG, OnUpdateViewCameradlg)
  //}}AFX_MSG_MAP
  ON_MESSAGE(WM_APP + 100, OnNextImage)
  ON_MESSAGE(WM_APP + 101, OnThreadError)
  ON_MESSAGE(WM_APP + 102, OnConvertDialog)
  ON_WM_DESTROY()
END_MESSAGE_MAP()

static UINT indicators[] =
{
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
  // TODO: add member initialization code here
  m_bRecord = FALSE;
  m_bPlay = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  // create a view to occupy the client area of the frame
  if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
    CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
  {
    TRACE0("Failed to create view window\n");
    return -1;
  }
  
  if (!m_wndToolBar.CreateEx(this) ||
    !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
  {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  if (!m_wndReBar.Create(this) ||
    !m_wndReBar.AddBar(&m_wndToolBar))
  {
    TRACE0("Failed to create rebar\n");
    return -1;      // fail to create
  }

  if (!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Failed to create status bar\n");
    return -1;      // fail to create
  }

  // TODO: Remove this if you don't want tool tips
  m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
    CBRS_TOOLTIPS | CBRS_FLYBY);


  m_Camera = new CSC2Class();
  if(m_Camera->OpenCamera(GetSafeHwnd()) != PCO_NOERROR)
  {
    CMenu *menuMain;    // handle to main menu          
    
    AfxMessageBox("Open camera failed. No camera found!", MB_ICONERROR, 0);
    menuMain = GetMenu();
    menuMain->DeleteMenu(2, MF_BYPOSITION);
    menuMain->DeleteMenu(1, MF_BYPOSITION);
    m_wndToolBar.ShowWindow(SW_HIDE);
  }
  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  if( !CFrameWnd::PreCreateWindow(cs) )
    return FALSE;
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
  cs.lpszClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,
      ::LoadCursor(NULL, IDC_ARROW),
      (HBRUSH) ::GetStockObject(WHITE_BRUSH),
      ::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME)));
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
  // forward focus to the view window
  m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
  // let the view have first crack at the command
  if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;

  // otherwise, do default handling
  return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnStartRecord() 
{
  m_Camera->StartRecord();
  m_bRecord = TRUE;
  m_bPlay = FALSE;
}

void CMainFrame::OnUpdateStartRecord(CCmdUI* pCmdUI) 
{
  if(m_bRecord || m_bPlay)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
  if(m_bRecord)
    pCmdUI->SetCheck(1);
  else
    pCmdUI->SetCheck(0);
}

void CMainFrame::OnStartPlay() 
{
  m_Camera->StartPlay();
  m_bRecord = FALSE;
  m_bPlay = TRUE;
}

void CMainFrame::OnUpdateStartPlay(CCmdUI* pCmdUI) 
{
  if(m_bRecord || m_bPlay)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
  if(m_bPlay)
    pCmdUI->SetCheck(1);
  else
    pCmdUI->SetCheck(0);
}

void CMainFrame::OnStopCamera() 
{
  if(m_bRecord)
    m_Camera->StopRecord();
  if(m_bPlay)
    m_Camera->StopPlay();
  m_bRecord = FALSE;
  m_bPlay = FALSE;
}

LRESULT CMainFrame::OnNextImage(WPARAM, LPARAM)         // Message from the thread, to display the next image. 
{
  m_wndView.SetBmp(m_Camera->GetBmpHandle(), m_Camera->GetXRes(), m_Camera->GetYRes());  
  return 0;
}

void CMainFrame::OnAutominmax() 
{
  m_Camera->AutoGain();
}

void CMainFrame::OnViewConvertdlg() 
{
  if((m_Camera->GetDialog(TRUE)) >= 0)
    m_Camera->CloseConvertDialog();  
  else
    m_Camera->OpenConvertDialog();  
}

void CMainFrame::OnUpdateViewConvertdlg(CCmdUI* pCmdUI) 
{
  if((  m_Camera->GetDialog(TRUE)) >= 0)
    pCmdUI->SetCheck(1);
  else
    pCmdUI->SetCheck(0);
}

void CMainFrame::OnViewCameradlg() 
{
  if((m_Camera->GetDialog(FALSE)) >= 0)
    m_Camera->CloseCamDialog();  
  else
    m_Camera->OpenCamDialog();  
}

void CMainFrame::OnUpdateViewCameradlg(CCmdUI* pCmdUI) 
{
  if((  m_Camera->GetDialog(FALSE)) >= 0)
    pCmdUI->SetCheck(1);
  else
    pCmdUI->SetCheck(0);
}

LRESULT CMainFrame::OnThreadError(WPARAM, LPARAM)// Thread stopped. 
{
  if(m_bRecord)
    m_Camera->StopRecord();
  if(m_bPlay)
    m_Camera->StopPlay();
  m_bRecord = FALSE;
  m_bPlay = FALSE;

  return TRUE;
}

LRESULT CMainFrame::OnConvertDialog(WPARAM, LPARAM lp)
{
  PCO_ConvDlg_Message *pcnv;

  pcnv = (PCO_ConvDlg_Message*)lp;

  if(pcnv->wCommand == PCO_CNV_DLG_CMD_WHITEBALANCE)
  {
    m_Camera->WhiteBalance();
  }
  if(pcnv->wCommand == PCO_CNV_DLG_CMD_UPDATE)
  {
    m_Camera->Convert();
  }
  return TRUE;
}


void CMainFrame::OnDestroy()
{
  if(m_Camera != NULL)
  {
    m_Camera->CloseCamera();
    delete(m_Camera);
  }
  CFrameWnd::OnDestroy();
}
