#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		

class CKatanyaApp : public CWinAppEx
{
public:
	CKatanyaApp();

	public:
	virtual BOOL InitInstance();

protected:
	ULONG_PTR	m_gdiplusToken;
	void SetClassName();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CKatanyaApp theApp;