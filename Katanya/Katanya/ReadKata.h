#pragma once

struct KataInfo
{
	CString kata;
	CString arti;
	CString show;
};

class ReadKata
{
public:
	ReadKata(void);
	virtual ~ReadKata(void);

public:	
	BOOL InitKataInfos1();
	BOOL InitKataInfos2();

	std::vector<KataInfo> GetKatasInfo1() { return m_KataInfos1; }
	std::vector<KataInfo> GetKatasInfo2() { return m_KataInfos2; }

	int GetCount1() { return m_KataInfos1.size(); };
	int GetCount2() { return m_KataInfos2.size(); };

	void ReadData1(int nIndex, CString &kata, CString &arti, CString &show);
	void ReadData2(int nIndex, CString &kata, CString &arti, CString &show);

private:
	CString GetModulePath();
	CString GetOpenKataFilePath(CString strFileName);

	BOOL GetSplitAppsTotal(CString strInput, CStringArray& strResultArr);
	BOOL GetSplitAppsPart(CString strInput, CStringArray& strResultArr);
	void GetSplitString(CString strInput, CString &strName, CString &strValue);
    BOOL GetSplitParams(CString strInput, CStringArray& strResultArr);

	void ClearKataInfo();

	std::vector<KataInfo> m_KataInfos1;
	std::vector<KataInfo> m_KataInfos2;
};
