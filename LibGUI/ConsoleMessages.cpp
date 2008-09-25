// ConsoleMessages.cpp : implementation file
//

#include "stdafx.h"
//#include "GTScalp.h" // provides dialog box constants
#include "ConsoleMessages.h"

#include "assert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CConsoleMessages dialog

IMPLEMENT_DYNAMIC(CConsoleMessages, CGUIFrameBase)

CConsoleMessages::CConsoleMessages(CWnd* pParent /*=NULL*/)
	: bDialogReady( false ), CGUIFrameBase( pParent )
{

  CGUIFrameBase::SetTitleBarText( _T( "Console Messages" ) );
  assert( CGUIFrameBase::Create() );
  CGUIFrameBase::SetPosition( 100, 800, 500, 1200 );

  CRect rect1, rect2;
  //GetWindowRect(&rect1);
  //rect1.MoveToXY(10,10);
  //MoveWindow(&rect1);

  GetClientRect( &rect1 );
  rect2.SetRect( 5, 5, rect1.right - 5, rect1.bottom - 5 );
  m_ceMessages.Create( WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_READONLY, rect2, this, 2 );
  //ceMessages.MoveWindow( &rect2 );

  m_ceMessages.EnableScrollBar( SB_VERT, ESB_ENABLE_BOTH );
  m_ceMessages.EnableWindow( );

  VERIFY( m_font.CreateFont( 
   14,                        // nHeight
   0,                         // nWidth
   0,                         // nEscapement
   0,                         // nOrientation
   FW_NORMAL,                 // nWeight
   FALSE,                     // bItalic
   FALSE,                     // bUnderline
   0,                         // cStrikeOut
   ANSI_CHARSET,              // nCharSet
   OUT_DEFAULT_PRECIS,        // nOutPrecision
   CLIP_DEFAULT_PRECIS,       // nClipPrecision
   DEFAULT_QUALITY,           // nQuality
   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
   "Arial"));                 // lpszFacename
  m_ceMessages.SetFont( &m_font );

  bDialogReady = true;
}

afx_msg void CConsoleMessages::OnSize( UINT i, int x, int y ) {
  if ( bDialogReady ) {
    CGUIFrameBase::OnSize( i, x, y );
    CRect rect1, rect2;
    GetClientRect( &rect1 );
    rect2.SetRect( 5, 5, rect1.right - 5, rect1.bottom - 5 );
    m_ceMessages.MoveWindow( &rect2 );
  }
}

CConsoleMessages::~CConsoleMessages() {
  //DestroyWindow();
  // need to destroy CDialog and CMessageList?
}

/*
void CConsoleMessages::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MESSAGES, ceMessages);
  //DDX_Text(pDX, IDC_MESSAGES, sMessageList);
}
*/

// need to make this more elegant... need some sort of append capability

void CConsoleMessages::Write(const CString &sMessage) {
  m_ceMessages.ReplaceSel( (LPCTSTR) sMessage );
  //sMessageList.Insert(0, sMessage);
  //UpdateData(FALSE);
}

void CConsoleMessages::Write(const char *sMessage) {
  m_ceMessages.ReplaceSel( sMessage );
  //sMessageList.Insert(0, sMessage);
  //UpdateData(FALSE);
}

void CConsoleMessages::Write(const std::string &sMessage) {
  m_ceMessages.ReplaceSel( sMessage.c_str() );
  //sMessageList.Insert(0, sMessage.c_str() );
  //UpdateData(FALSE);
}

void CConsoleMessages::WriteLine(const CString &sMessage) {
  m_ceMessages.ReplaceSel( (LPCTSTR) sMessage );
  WriteLine();
  //sMessageList.Insert(0, _T( "\r\n" ) );
  //sMessageList.Insert(0, sMessage);
  //UpdateData(FALSE);
}

void CConsoleMessages::WriteLine( const char *sMessage ) {
  m_ceMessages.ReplaceSel( sMessage );
  WriteLine();
  //sMessageList.Insert(0, _T( "\r\n" ) );
  //sMessageList.Insert(0, sMessage);
  //UpdateData(FALSE);
}

void CConsoleMessages::WriteLine() {
  m_ceMessages.ReplaceSel( _T( "\r\n" ) );
  //sMessageList.Insert(0, _T( "\r\n" ) );
  //UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CConsoleMessages, CGUIFrameBase)
  ON_WM_SIZE()
END_MESSAGE_MAP()

// CConsoleMessages message handlers