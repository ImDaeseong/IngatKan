/////////////////////////////////////////////////////////////////////////////
// SystemTray.h : header file
//



#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

#include <afxtempl.h>


class CKatanyaDlg;
/////////////////////////////////////////////////////////////////////////////
// CSystemTray window
class CSystemTray : public CWnd
{
// Construction/destruction
public:
    CSystemTray();
    CSystemTray(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID, int nDefaultMenuID, CKatanyaDlg* pMainDlg);
    virtual ~CSystemTray();
	
    DECLARE_DYNAMIC(CSystemTray)

// Operations
public:
    BOOL Enabled() { return m_bEnabled; }
    BOOL Visible() { return !m_bHidden; }

    // Create the tray icon
	BOOL Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID, int nDefaultMenuID, CKatanyaDlg* pMainDlg);
	void DestroyTray();


    // Change or retrieve the icon displayed
    BOOL  SetIcon(HICON hIcon);
    BOOL  SetIcon(LPCTSTR lpszIconName);
    BOOL  SetIcon(UINT nIDResource);
    BOOL  SetStandardIcon(LPCTSTR lpIconName);
    BOOL  SetStandardIcon(UINT nIDResource);
	BOOL  SetToolTipMsg(LPCTSTR pszMessage);

    HICON GetIcon() const;
    void  HideIcon();
    void  ShowIcon();
    void  RemoveIcon();
    void  MoveToRight();	

    // For icon animation
    BOOL  SetIconList(UINT uFirstIconID, UINT uLastIconID); 
    BOOL  SetIconList(HICON* pHIconList, UINT nNumIcons); 
    BOOL  Animate(UINT nDelayMilliSeconds, int nNumSeconds = -1);
    BOOL  StepAnimation();
    BOOL  StopAnimation();

    // Change or retrieve the window to send notification messages to
    BOOL  SetNotificationWnd(CWnd* pNotifyWnd);
    CWnd* GetNotificationWnd() const;

    // Default handler for tray notification message
    virtual LRESULT OnTrayNotification(WPARAM uID, LPARAM lEvent);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSystemTray)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
    void Initialise();

    BOOL            m_bEnabled;   // does O/S support tray icon?
    BOOL            m_bHidden;    // Has the icon been hidden?
    NOTIFYICONDATA  m_tnd;

	static UINT s_uTrayMessage;
	
	CKatanyaDlg* m_pMainDlg;

    CArray<HICON, HICON> m_IconList;
    static UINT  m_nIDEvent;

    UINT         m_uIDTimer;
    int          m_nCurrentIcon;
    
	COleDateTime m_StartTime;

    int          m_nAnimationPeriod;
    int          m_DefaultMenuItemID;
	HICON        m_hSavedIcon;
	

// Generated message map functions
protected:
	//{{AFX_MSG(CSystemTray)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnTrayShow(WPARAM wParam, LPARAM lParam);		//트레이아이콘 메시지
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

#endif

/////////////////////////////////////////////////////////////////////////////
