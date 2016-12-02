#include "stdafx.h"
#include "Katanya.h"
#include "KatanyaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CKatanyaDlg::CKatanyaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKatanyaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pBackSkin	= NULL;	

	m_nScreenSizeX = 0;
	m_nScreenSizeY = 0;

	m_nTimerCheckCount = 10;
	m_nReadIndex1 = 0;
	m_nReadIndex2 = 0;

	m_strkata1 = "";
	m_strarti1 = "";
	m_strshow1 = "";		
	m_strkata2 = "";
	m_strarti2 = "";
	m_strshow2 = "";	
}

void CKatanyaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
}

BEGIN_MESSAGE_MAP(CKatanyaDlg, CDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DISPLAYCHANGE, OnDisplayChange)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_TRAYMENU_EXIT, CKatanyaDlg::OnTraymenuExit)
END_MESSAGE_MAP()

void CKatanyaDlg::OnDestroy() 
{
	m_TrayIcon.DestroyTray();

	KillTimer(1);
	
	if(m_pBackSkin != NULL)
		delete m_pBackSkin;
	m_pBackSkin = NULL;	

	CDialog::OnDestroy();
}

void CKatanyaDlg::OnTimer(UINT nIDEvent) 
{	
	if(nIDEvent == 1)
	{
		m_nTimerCheckCount++;

		if(m_nTimerCheckCount >= 10)
		{
			SetKataData();

			m_nTimerCheckCount = 0;
		}
	}	
	
	CDialog::OnTimer(nIDEvent);
}

void CKatanyaDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{ 
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	SetTopActivate(); 
}

BOOL CKatanyaDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CKatanyaDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (nType == SIZE_MAXIMIZED || nType == SIZE_RESTORED)
		Invalidate();
}

LRESULT CKatanyaDlg::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
	CDC* pDC = GetDC();
	if(pDC != NULL)
	{
		DrawSkin(pDC);
		ReleaseDC(pDC);
	}
	
	int nScreenSizeX = GetSystemMetrics(SM_CXSCREEN);
	int nScreenSizeY = GetSystemMetrics(SM_CYSCREEN);
	if( nScreenSizeX != m_nScreenSizeX || nScreenSizeY != m_nScreenSizeY )
	{
		m_nScreenSizeX = nScreenSizeX;
		m_nScreenSizeY = nScreenSizeY;
		MoveLocationDialog();
	}
	return 0;
}

void CKatanyaDlg::OnPaint()
{
	CPaintDC dc(this); 
	DrawSkin(&dc);
}

void CKatanyaDlg::InitData()
{
	m_objKata.InitKataInfos1();
	m_objKata.InitKataInfos2();

	/*
	BOOL bLoad = m_objKata.InitKataInfos1();
    if(bLoad)
	{
		std::vector<KataInfo> m_kataInfo =  m_objKata.GetKatasInfo1();
		for (int i = 0; i < m_kataInfo.size(); i++)
		{	
			m_kataInfo[i].kata;
			m_kataInfo[i].arti;
			m_kataInfo[i].show;			
		}		
		m_kataInfo.clear();
	}	

	bLoad = m_objKata.InitKataInfos2();
    if(bLoad)
	{
		std::vector<KataInfo> m_kataInfo =  m_objKata.GetKatasInfo2();
		for (int i = 0; i < m_kataInfo.size(); i++)
		{	
			m_kataInfo[i].kata;
			m_kataInfo[i].arti;
			m_kataInfo[i].show;			
		}		
		m_kataInfo.clear();
	}	
	*/
}

void CKatanyaDlg::SetKataData()
{	
	if( m_objKata.GetCount1() == m_nReadIndex1)
		m_nReadIndex1 = 0;

	if( m_objKata.GetCount2() == m_nReadIndex2)
		m_nReadIndex2 = 0;

	if(m_objKata.GetCount1() > 0)
	{
		m_objKata.ReadData1(m_nReadIndex1, m_strkata1, m_strarti1, m_strshow1);
		m_nReadIndex1++;
	}

	if( m_objKata.GetCount2() > 0)
	{
		m_objKata.ReadData2(m_nReadIndex2, m_strkata2, m_strarti2, m_strshow2);
		m_nReadIndex2++;
	}
	Invalidate();
}

BOOL CKatanyaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW | WS_EX_LAYERED);
		
	InitData();

	if(!LoadSkin())
	{
		CDialog::OnCancel();
		return FALSE;
	}

	CDC* pDC = GetDC();
	DrawSkin(pDC);
	ReleaseDC(pDC);
	
	CString strTrayMsg;
	strTrayMsg.Format(_T("Katanya (ver.%s)"), "1");
	m_TrayIcon.Create(NULL, WM_TRAY_MENUBAR, strTrayMsg, AfxGetApp()->LoadIcon(IDR_MAINFRAME), IDR_TRAY_MENU, 0, this);

	//if(!IsStartRegister())
	//	SetStartRegister();
	SetStartRegister();

	SetTimer(1, 1000, NULL);
		
	return TRUE; 
}

CString CKatanyaDlg::GetModulePath()
{
	char cTemp[MAX_PATH];
	char *spzRealDirEnd;
	CString strModulePath;

	GetModuleFileName(NULL, cTemp, MAX_PATH);  
	spzRealDirEnd = strrchr(cTemp, '\\');
	*spzRealDirEnd = '\0';
	strModulePath = (CString)cTemp;
	return strModulePath;
}

BOOL CKatanyaDlg::SetAutoStart(LPCTSTR szKeyValue, LPCTSTR szFilePath)
{	
	CRegKey regKey;
	if (regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")) != ERROR_SUCCESS)
	{
		regKey.Close();
		return FALSE;
	}

	regKey.SetStringValue(szKeyValue, szFilePath);
	regKey.Close();

	return TRUE;	
}

BOOL CKatanyaDlg::IsExistAutoRun(LPCTSTR szKey, LPCTSTR szProgPath)
{	
	char szBuffer [MAX_PATH + 1] = {0, };
	DWORD dwCount = 0;

	CRegKey regKey;

	if (regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), KEY_READ) != ERROR_SUCCESS)
	{
		regKey.Close();
		return FALSE;
	}

	dwCount = REG_BUFF_SIZE + 1;
	
	if (ERROR_SUCCESS != regKey.QueryStringValue(szKey, szBuffer, &dwCount))
	{
		regKey.Close();
		return FALSE;
	}

	regKey.Close();

	if(_stricmp(szProgPath, szBuffer) != 0)
		return FALSE;	

	return TRUE;
}

void CKatanyaDlg::SetStartRegister()
{	
	CString strFile;
	strFile.Format("%s\\Katanya.exe", GetModulePath());
	SetAutoStart("KatanyaRun", strFile);
}

BOOL CKatanyaDlg::IsStartRegister()
{
	CString strFile;
	strFile.Format("%s\\Katanya.exe", GetModulePath());
	return IsExistAutoRun("KatanyaRun", strFile);
}

void CKatanyaDlg::OnTraymenuExit()
{
	CDialog::OnOK();
}

BOOL CKatanyaDlg::LoadSkin()
{
	m_pBackSkin = new CGdiPlusBitmapResource;
	if(!m_pBackSkin->Load(IDB_PNG_BG, "PNG", AfxGetApp()->m_hInstance))
	{
		delete m_pBackSkin;
		m_pBackSkin = NULL;
		return FALSE;
	}
		
	MoveLocationDialog();

	return TRUE;
}

void CKatanyaDlg::DrawSkin(CDC* pDC)
{
	CDC memDC;
	CBitmap bmp;
	CBitmap* bmp_old;

	CRect rect;
	GetWindowRect(&rect);

	int cx = rect.Width();
	int cy = rect.Height();

	memDC.CreateCompatibleDC(pDC);

	BITMAPINFO bmInfo;
	memset(&bmInfo, 0x00, sizeof(BITMAPINFO));
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth = cx;
	bmInfo.bmiHeader.biHeight = cy;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = 32;
	bmInfo.bmiHeader.biCompression = BI_RGB;
	bmInfo.bmiHeader.biSizeImage = 0;
	bmInfo.bmiHeader.biClrUsed = 0;
	bmInfo.bmiHeader.biClrImportant = 0;

	LPBYTE pbmpBits = NULL;
	HBITMAP hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(), (LPBITMAPINFO)&bmInfo, DIB_RGB_COLORS, (void **)&pbmpBits, NULL, 0);
	if(hBitmap == NULL)
		bmp.CreateCompatibleBitmap(pDC, cx, cy);
	else
		bmp.Attach(hBitmap);

	bmp_old = memDC.SelectObject(&bmp);
	Graphics gps(memDC.GetSafeHdc());

	gps.DrawImage(m_pBackSkin->m_pBitmap,Rect(0, 0, m_pBackSkin->m_pBitmap->GetWidth(), m_pBackSkin->m_pBitmap->GetHeight()), 
		0,0,m_pBackSkin->m_pBitmap->GetWidth(), m_pBackSkin->m_pBitmap->GetHeight(),UnitPixel);
	
	SetKata(gps);

	CPoint ptWindowScreenPosition(rect.TopLeft());
	CSize szWindow(cx, cy);

	BLENDFUNCTION blendPixelFunction= { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	CPoint ptSrc(0,0);

	HDC hdc = gps.GetHDC();
	BOOL bRet= ::UpdateLayeredWindow(GetSafeHwnd(),pDC->GetSafeHdc(),&ptWindowScreenPosition,&szWindow,hdc,&ptSrc,0,&blendPixelFunction,ULW_ALPHA);
	gps.ReleaseHDC(hdc);
	memDC.SelectObject(bmp_old);
	bmp.DeleteObject();
	memDC.DeleteDC();
}

void CKatanyaDlg::MoveLocationDialog()
{
	m_nScreenSizeX = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenSizeY = GetSystemMetrics(SM_CYSCREEN);
	int cx = m_pBackSkin->m_pBitmap->GetWidth();
	int cy = m_pBackSkin->m_pBitmap->GetHeight();

	RECT rcWorkArea;
	SystemParametersInfo (SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	MoveWindow(rcWorkArea.left + 5, rcWorkArea.bottom - cy - 10,  cx, cy);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);	
}

void CKatanyaDlg::SetTopActivate()
{
	::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
}

void CKatanyaDlg::SetKata(Graphics& gps)
{	
USES_CONVERSION;

	Gdiplus::Font font1(L"µ¸¿ò", 20, FontStyleBold, UnitPixel);
	SolidBrush brush1(Color(234, 137, 6));

	Gdiplus::Font font2(L"µ¸¿ò", 19, FontStyleBold, UnitPixel);
	SolidBrush brush2(Color(64, 193, 255));

	StringFormat stringFormat(StringFormatFlagsDisplayFormatControl);
	stringFormat.SetAlignment(StringAlignmentCenter);	
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	
	CRect rect;
    GetClientRect(&rect);

	if(m_strshow1 == "1")
	{	
		RectF rectF1(REAL(rect.left + 5), REAL(rect.top + 20), REAL(rect.Width()), REAL(30));
		gps.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
		gps.DrawString(A2W(m_strkata1), -1, &font1, rectF1, &stringFormat, &brush1);

		RectF rectF2(REAL(rect.left + 5), REAL(rect.top + 50), REAL(rect.Width()), REAL(30));
		gps.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
		gps.DrawString(A2W(m_strarti1), -1, &font2, rectF2, &stringFormat, &brush2);
	}

	if(m_strshow2 == "1")
	{
		RectF rectF3(REAL(rect.left + 5), REAL(rect.top + 100), REAL(rect.Width()), REAL(30));
		gps.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
		gps.DrawString(A2W(m_strkata2), -1, &font1, rectF3, &stringFormat, &brush1);

		RectF rectF4(REAL(rect.left + 5), REAL(rect.top + 130), REAL(rect.Width()), REAL(30));
		gps.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
		gps.DrawString(A2W(m_strarti2), -1, &font2, rectF4, &stringFormat, &brush2);
	}
}
