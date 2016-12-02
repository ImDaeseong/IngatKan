#include "StdAfx.h"
#include "ReadKata.h"

ReadKata::ReadKata(void)
{
	ClearKataInfo();
}

ReadKata::~ReadKata(void)
{
	ClearKataInfo();
}

void ReadKata::ClearKataInfo()
{
	m_KataInfos1.clear();
	m_KataInfos2.clear();
}

CString ReadKata::GetModulePath()
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

BOOL ReadKata::GetSplitAppsTotal(CString strInput, CStringArray& strResultArr)
{
	BOOL bFind = FALSE;

	strResultArr.RemoveAll();
	CString strOutput(_T(""));
	int nCountLeft = strInput.Find(_T("{"));
	int nCountRight = strInput.Find(_T("}"));
	while(nCountRight>nCountLeft)
	{
		strOutput = strInput.Mid(nCountLeft+1, nCountRight - nCountLeft - 1);
		strResultArr.Add(strOutput);
		strInput = strInput.Mid(nCountRight+1);
		nCountLeft = strInput.Find(_T("{"));
		nCountRight = strInput.Find(_T("}"));
		bFind = TRUE;
	}	
	return bFind;
}

BOOL ReadKata::GetSplitAppsPart(CString strInput, CStringArray& strResultArr)
{
	BOOL bFind = FALSE;

	strResultArr.RemoveAll();
	int nCount = strInput.Find(_T(","));
	int nLength = 0;	
	CString strPrefix, strNext;
	strNext = strInput;
	CString strTmp;
	while(nCount!=-1)
	{
		strPrefix = strNext.Left(nCount);
		strResultArr.Add(strPrefix);
		nLength = strNext.GetLength();
		strTmp = strNext.Right(nLength - nCount - 1);
		strNext = strTmp;
		nCount = strNext.Find(_T(","));
		bFind = TRUE;
	}
	if(strNext != "")strResultArr.Add(strNext);
	return bFind;
}

void ReadKata::GetSplitString(CString strInput, CString &strName, CString &strValue)
{
	int nCount = strInput.Find(_T(":"));
	int nLength = strInput.GetLength();
	strName = strInput.Left(nCount);
	strValue = strInput.Right(nLength - nCount - 1);

	strName.Replace("\"","");
	strName.TrimLeft();
	strName.TrimRight();

	strValue.Replace("\"","");
	strValue.TrimLeft();
	strValue.TrimRight();
}

CString ReadKata::GetOpenKataFilePath(CString strFileName)
{	
	CString strFileFullPath;
	strFileFullPath.Format("%s\\%s", GetModulePath(), strFileName);
	if(!::PathFileExists(strFileFullPath))
		return ""; 

	wstring content;
	CFile file;
	file.Open(strFileFullPath, CFile::modeRead);
	ReadFile::readFile(file, content);
	file.Close();

	CString strTotalContent(content.c_str());
	return strTotalContent;	
}

BOOL ReadKata::InitKataInfos1()
{
	CString strInput = GetOpenKataFilePath("Katanya1.json");
	if(strInput == "")
		return FALSE;

	CString strName;
	CString strValue;
	CStringArray strTotalApp;
	CStringArray strDetailApp;

	if(GetSplitAppsTotal(strInput, strTotalApp))
	{		
		for(int i=0; i < strTotalApp.GetCount(); i++)
		{			
			if( GetSplitAppsPart(strTotalApp.GetAt(i), strDetailApp) )
			{
				KataInfo AppInfos;

				for(int k=0; k < strDetailApp.GetCount(); k++)
				{				
					GetSplitString(strDetailApp.GetAt(k), strName, strValue);

					if(lstrcmpi(strName, "kata") == 0)
						AppInfos.kata = strValue;
					else if(lstrcmpi(strName, "arti") == 0)
						AppInfos.arti = strValue;
					else if(lstrcmpi(strName, "show") == 0)
						AppInfos.show = strValue;
				}		

				m_KataInfos1.push_back(AppInfos);
			}
		}

		strDetailApp.RemoveAll();
		strTotalApp.RemoveAll();
	}	
	return TRUE;
}

BOOL ReadKata::InitKataInfos2()
{
	CString strInput = GetOpenKataFilePath("Katanya2.json");
	if(strInput == "")
		return FALSE;

	CString strName;
	CString strValue;
	CStringArray strTotalApp;
	CStringArray strDetailApp;

	if(GetSplitAppsTotal(strInput, strTotalApp))
	{		
		for(int i=0; i < strTotalApp.GetCount(); i++)
		{			
			if( GetSplitAppsPart(strTotalApp.GetAt(i), strDetailApp) )
			{
				KataInfo AppInfos;

				for(int k=0; k < strDetailApp.GetCount(); k++)
				{				
					GetSplitString(strDetailApp.GetAt(k), strName, strValue);

					if(lstrcmpi(strName, "kata") == 0)
						AppInfos.kata = strValue;
					else if(lstrcmpi(strName, "arti") == 0)
						AppInfos.arti = strValue;
					else if(lstrcmpi(strName, "show") == 0)
						AppInfos.show = strValue;
				}				

				m_KataInfos2.push_back(AppInfos);
			}
		}

		strDetailApp.RemoveAll();
		strTotalApp.RemoveAll();
	}	
	return TRUE;
}

void ReadKata::ReadData1(int nIndex, CString &kata, CString &arti, CString &show)
{
	try
	{
		kata = m_KataInfos1[nIndex].kata;
		arti = m_KataInfos1[nIndex].arti;
		show = m_KataInfos1[nIndex].show;
	}
	catch(...)
	{
		kata = "";
		arti = "";
		show = "";
	}
}

void ReadKata::ReadData2(int nIndex, CString &kata, CString &arti, CString &show)
{
	try
	{
		kata = m_KataInfos2[nIndex].kata;
		arti = m_KataInfos2[nIndex].arti;
		show = m_KataInfos2[nIndex].show;
	}
	catch(...)
	{
		kata = "";
		arti = "";
		show = "";
	}
}