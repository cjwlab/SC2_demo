#ifndef SC2CLASS
#define SC2CLASS

#include "windows.h"
#include "include\sc2_SDKAddendum.h"
#include "include\sc2_SDKStructures.h"
#include "include\SC2_CamExport.h"
#include "include\pco_structures.h"
#include "include\pco_convstructures.h"
#include "include\pco_convexport.h"
#include "include\pco_convdlgexport.h"
#include "include\PCO_Err.h"
#include "include\Sc2_DialogExport.h"

class CSC2Class
{
  // function declarations
public:
  CSC2Class();
  ~CSC2Class();
  int OpenCamera(HWND hwnd = NULL);
  void CloseCamera();
  void OpenConvertDialog();
  void CloseConvertDialog();
  void OpenCamDialog();
  void CloseCamDialog();
  int StartRecord();
  void StopRecord();
  int StartPlay();
  void StopPlay();

  int GetXRes();
  int GetYRes();
  void Disconnected();
  void Connected();
  int GetBitPix();
  int GetDialog(bool bconv);
  void AutoGain();
  void WhiteBalance();
  int  Convert();

  HBITMAP GetBmpHandle(){return m_hBmp;};

  DWORD SC2Thread();

  unsigned char **m_stack;

  bool m_bThreadRun;
  bool m_bPlay;
  bool m_bFirstArm;

  HANDLE m_hMutex; 
  
private:
  void PrepareBuffers();
  void ClearBuffers();
  void SetBWPalette();
  int  GetDemosaickingMode(int wroix0, int wroiy0);
  
  // variables
private:
  HANDLE hCam;
  PCO_General strGeneral;
  PCO_CameraType strCamType;
  PCO_Sensor strSensor;
  PCO_Description strDescription;
  PCO_Timing strTiming;
  PCO_Storage strStorage;
  PCO_Recording strRecording;
  PCO_Image strImage;

  CWinThread*  m_wthWorker;
  HANDLE m_hEvent;

#define NUMBER_OF_BUFFERS 8

  HANDLE ghEvents[NUMBER_OF_BUFFERS];
  WORD* m_camImage[NUMBER_OF_BUFFERS];
  WORD m_wBufferNr2[NUMBER_OF_BUFFERS];


  WORD* m_pic12;
  BYTE* m_pic8;
  int m_iColorCam;

  HANDLE hBWConvert;
  HANDLE hColConvert;

  HWND m_hwndMain;
  HBITMAP m_hBmp;
  WORD m_wBufferNr;
  HANDLE hLutDialog;
  int m_iColorPatternType;
  BOOL m_bConnectionLost;
  HDC m_myHdc;
  HANDLE m_hSC2Dlg;
  WORD m_wXResAct, m_wYResAct, m_wXResMax, m_wYResMax;
  DWORD m_dwValidImageCnt, m_dwMaxImageCnt;
  WORD m_wActSeg;
  CPalette m_myhpal;
  HPALETTE m_oldhpal;
  /* , MemHDC;
  RECT rect;
  */
};

#endif