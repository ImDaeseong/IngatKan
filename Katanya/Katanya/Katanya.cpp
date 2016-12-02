#include "stdafx.h"
#include "Katanya.h"
#include "KatanyaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CKatanyaApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CKatanyaApp::CKatanyaApp()
{
	m_gdiplusToken = NULL;
}

CKatanyaApp theApp;

BOOL CKatanyaApp::InitInstance()
{
	HANDLE hMutex = ::CreateMutex(NULL, FALSE, "katanyaModuleMiniInstance_");
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
		return FALSE;
	
	CoInitialize(NULL);

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);	
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	SetClassName();

	CKatanyaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	return FALSE;
}

int CKatanyaApp::ExitInstance()
{
	if(m_gdiplusToken != NULL)
	{
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}

	CoUninitialize();

	return CWinAppEx::ExitInstance();
}

void CKatanyaApp::SetClassName()
{
	WNDCLASS wc;
	GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);;

	wc.lpszClassName = _T("katanyaModuleMini");
	AfxRegisterClass(&wc);
}