#pragma once
#include "afxwin.h"

class CKatanyaDlg : public CDialog
{
public:
	CKatanyaDlg(CWnd* pParent = NULL);	

	enum { IDD = IDD_KATANYA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	CSystemTray	m_TrayIcon;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
    afx_msg void OnTraymenuExit();

private:
	CString GetModulePath();
	void SetStartRegister();
	BOOL IsStartRegister();
	BOOL IsExistAutoRun(LPCTSTR szKey, LPCTSTR szProgPath);
	BOOL SetAutoStart(LPCTSTR szKeyValue, LPCTSTR szFilePath);
	void SetKata(Graphics& gps);
	void SetKataData();
	void InitData();
	void SetTopActivate();
	void MoveLocationDialog();
	void DrawSkin(CDC* pDC);
	BOOL LoadSkin();
	CGdiPlusBitmapResource* m_pBackSkin;	

	int m_nScreenSizeX;
	int m_nScreenSizeY;

	int m_nTimerCheckCount;
	int m_nReadIndex1;
	int m_nReadIndex2;

	CString m_strkata1;
	CString m_strarti1;
	CString m_strshow1;		
	CString m_strkata2;
	CString m_strarti2;
	CString m_strshow2;	

	ReadKata m_objKata;
};
