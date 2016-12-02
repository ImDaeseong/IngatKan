/////////////////////////////////////////////////////////////////////////////
// SystemTray.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
    
#include "stdafx.h"
#include "SystemTray.h"
#include "KatanyaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSystemTray, CWnd)

UINT CSystemTray::m_nIDEvent = 4267;
UINT CSystemTray::s_uTrayMessage = RegisterWindowMessage(__TEXT("TaskbarCreated"));


/////////////////////////////////////////////////////////////////////////////
// CSystemTray construction/creation/destruction
CSystemTray::CSystemTray()
{
    Initialise();
}

CSystemTray::CSystemTray(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID, int nDefaultMenuID, CKatanyaDlg* pMainDlg)
{
    Initialise();
    Create(pParent, uCallbackMessage, szToolTip, icon, uID, nDefaultMenuID, pMainDlg);
}

void CSystemTray::Initialise()
{
    memset(&m_tnd, 0, sizeof(m_tnd));
    m_bEnabled   = FALSE;
    m_bHidden    = FALSE;
    m_uIDTimer   = 0;
    m_hSavedIcon = NULL;
    m_DefaultMenuItemID = 0;
	m_pMainDlg = NULL;
}

BOOL CSystemTray::Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID, int nDefaultMenuID, CKatanyaDlg* pMainDlg)
{
    // this is only for Windows 95 (or higher)
    VERIFY(m_bEnabled = ( GetVersion() & 0xff ) >= 4);
    if (!m_bEnabled) return FALSE;

    // Make sure we avoid conflict with other messages
    ASSERT(uCallbackMessage >= WM_USER);

    // Tray only supports tooltip text up to 64 characters
    ASSERT(_tcslen(szToolTip) <= 64);

    // Create an invisible window
    CWnd::CreateEx(0, AfxRegisterWndClass(0), _T(""), WS_POPUP, 0,0,10,10, NULL, 0);

	m_DefaultMenuItemID = nDefaultMenuID;
    // load up the NOTIFYICONDATA structure
    m_tnd.cbSize = sizeof(NOTIFYICONDATA);
    m_tnd.hWnd   = pParent->GetSafeHwnd()? pParent->GetSafeHwnd() : m_hWnd;
    m_tnd.uID    = uID;
    m_tnd.hIcon  = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    _tcscpy(m_tnd.szTip, szToolTip);

	m_pMainDlg = pMainDlg;
    // Set the tray icon
    VERIFY(m_bEnabled = Shell_NotifyIcon(NIM_ADD, &m_tnd));
    return m_bEnabled;
}

void CSystemTray::DestroyTray()
{
	RemoveIcon();
    m_IconList.RemoveAll();
    DestroyWindow();
}

CSystemTray::~CSystemTray()
{
    RemoveIcon();
    m_IconList.RemoveAll();
    DestroyWindow();
}
/////////////////////////////////////////////////////////////////////////////
// CSystemTray icon manipulation
void CSystemTray::MoveToRight()
{
    HideIcon();
    ShowIcon();
}

void CSystemTray::RemoveIcon()
{
    if (!m_bEnabled) return;
    m_tnd.uFlags = 0;
    Shell_NotifyIcon(NIM_DELETE, &m_tnd);
    m_bEnabled = FALSE;
}

void CSystemTray::HideIcon()
{
    if (m_bEnabled && !m_bHidden) {
        m_tnd.uFlags = NIF_ICON;
        Shell_NotifyIcon (NIM_DELETE, &m_tnd);
        m_bHidden = TRUE;
    }
}

void CSystemTray::ShowIcon()
{
    if (m_bEnabled && m_bHidden) {
        m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIcon(NIM_ADD, &m_tnd);
        m_bHidden = FALSE;
    }
}

BOOL CSystemTray::SetIcon(HICON hIcon)
{
    if (!m_bEnabled) return FALSE;
    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CSystemTray::SetIcon(LPCTSTR lpszIconName)
{
    HICON hIcon = AfxGetApp()->LoadIcon(lpszIconName);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetIcon(UINT nIDResource)
{
    HICON hIcon = AfxGetApp()->LoadIcon(nIDResource);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetStandardIcon(LPCTSTR lpIconName)
{
    HICON hIcon = LoadIcon(NULL, lpIconName);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetStandardIcon(UINT nIDResource)
{
    HICON hIcon = LoadIcon(NULL, MAKEINTRESOURCE(nIDResource));

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetToolTipMsg(LPCTSTR pszMessage)
{
    if (!m_bEnabled) return FALSE;
    m_tnd.uFlags = NIF_TIP;
    _tcscpy(m_tnd.szTip, pszMessage);
    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}
 
HICON CSystemTray::GetIcon() const
{
    return (m_bEnabled)? m_tnd.hIcon : NULL;
}

BOOL CSystemTray::SetIconList(UINT uFirstIconID, UINT uLastIconID) 
{
	if (uFirstIconID > uLastIconID)
        return FALSE;

	UINT uIconArraySize = uLastIconID - uFirstIconID + 1;
	const CWinApp * pApp = AfxGetApp();
    ASSERT(pApp != 0);

    m_IconList.RemoveAll();
    try {
	    for (UINT i = uFirstIconID; i <= uLastIconID; i++)
		    m_IconList.Add(pApp->LoadIcon(i));
    }
    catch (CMemoryException *e)
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL CSystemTray::SetIconList(HICON* pHIconList, UINT nNumIcons)
{
    m_IconList.RemoveAll();

    try {
	    for (UINT i = 0; i <= nNumIcons; i++)
		    m_IconList.Add(pHIconList[i]);
    }
    catch (CMemoryException *e)
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL CSystemTray::Animate(UINT nDelayMilliSeconds, int nNumSeconds /*=-1*/)
{
    StopAnimation();

    m_nCurrentIcon = 0;
    m_StartTime = COleDateTime::GetCurrentTime();
    m_nAnimationPeriod = nNumSeconds;
    m_hSavedIcon = GetIcon();

	// Setup a timer for the animation
	m_uIDTimer = SetTimer(m_nIDEvent, nDelayMilliSeconds, NULL);

    return (m_uIDTimer != 0);
}

BOOL CSystemTray::StepAnimation()
{
    if (!m_IconList.GetSize())
        return FALSE;

    m_nCurrentIcon++;
    if (m_nCurrentIcon >= m_IconList.GetSize())
        m_nCurrentIcon = 0;

    return SetIcon(m_IconList[m_nCurrentIcon]);
}

BOOL CSystemTray::StopAnimation()
{
    BOOL bResult = FALSE;

    if (m_uIDTimer)
	    bResult = KillTimer(m_uIDTimer);
    m_uIDTimer = 0;

    if (m_hSavedIcon)
        SetIcon(m_hSavedIcon);
    m_hSavedIcon = NULL;

    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray notification window stuff

BOOL CSystemTray::SetNotificationWnd(CWnd* pWnd)
{
    if (!m_bEnabled) return FALSE;

    // Make sure Notification window is valid
    ASSERT(pWnd && ::IsWindow(pWnd->GetSafeHwnd()));

    m_tnd.hWnd = pWnd->GetSafeHwnd();
    m_tnd.uFlags = 0;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

CWnd* CSystemTray::GetNotificationWnd() const
{
    return CWnd::FromHandle(m_tnd.hWnd);
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray message handlers

BEGIN_MESSAGE_MAP(CSystemTray, CWnd)
	//{{AFX_MSG_MAP(CSystemTray)
	ON_WM_TIMER()
	ON_REGISTERED_MESSAGE(s_uTrayMessage, OnTrayShow)				//트레이아이콘 메시지
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSystemTray::OnTimer(UINT nIDEvent) 
{
    ASSERT(nIDEvent == m_nIDEvent);

    COleDateTime CurrentTime = COleDateTime::GetCurrentTime();
    COleDateTimeSpan period = CurrentTime - m_StartTime;
    if (m_nAnimationPeriod > 0 && m_nAnimationPeriod < period.GetTotalSeconds())
    {
        StopAnimation();
        return;
    }

    StepAnimation();
}

LRESULT CSystemTray::OnTrayNotification(UINT wParam, LONG lParam) 
{
    //Return quickly if its not for this tray icon
    if (wParam != m_tnd.uID)
        return 0L;
    CMenu menu, *pSubMenu;
	CWnd* pTarget = AfxGetMainWnd();

    // Clicking with right button brings up a context menu
    if (LOWORD(lParam) == WM_RBUTTONUP)
    {
        if (!menu.LoadMenu(m_tnd.uID)) return 0;
        if (!(pSubMenu = menu.GetSubMenu(0))) return 0;

        // Make chosen menu item the default (bold font)
        ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, FALSE);

        // Display and track the popup menu
        CPoint pos;
        GetCursorPos(&pos);
        pTarget->SetForegroundWindow();

		/*if(m_pMainDlg)
		{
			pSubMenu->EnableMenuItem(ID_TRAYMENU_END, MF_BYCOMMAND | MF_ENABLED);				
		}*/

        ::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, 
                         pTarget->GetSafeHwnd(), NULL);

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
		pTarget->PostMessage(WM_NULL, 0, 0);
        menu.DestroyMenu();
    }

	else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
    {
        // double click received, the default action is to execute default menu item
		pTarget->SetForegroundWindow();  		      
        pTarget->SendMessage(WM_COMMAND, MAKEWPARAM(m_DefaultMenuItemID, 0), 0);
    }
    return 1;
}

LRESULT CSystemTray::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if (message == m_tnd.uCallbackMessage)
        return OnTrayNotification(wParam, lParam);
	
	return CWnd::WindowProc(message, wParam, lParam);
}


LRESULT CSystemTray::OnTrayShow(WPARAM wParam, LPARAM lParam)		//트레이아이콘 메시지
{

	if (GetSafeHwnd() != NULL)
	{
		m_bHidden = TRUE;
		ShowIcon();
		return 0L;
	}

	
	return -1L;
}
