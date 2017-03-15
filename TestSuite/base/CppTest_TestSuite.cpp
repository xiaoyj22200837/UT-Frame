#include "CppTest_TestSuite.h"


int CppTest_TestSuite::nAssertFailFunNum = 0;
int CppTest_TestSuite::nOutOfTimeNum = 0;
int CppTest_TestSuite::nExceptNum = 0;
int CppTest_TestSuite::nSuccessNum = 0;
HWND CppTest_TestSuite::hwnd = XNULL;
Xwchar* CppTest_TestSuite::pszTestDataPath = XNULL;
bool CppTest_TestSuite::bIsITest = false;

void cpptestEqualAssert(bool b_equal, const char *szExpectedName, const char *szActualName, const char *szFileName, const char *szFunName, const int nLineNum)
{
	static const char *p = "Initialize Name";
	if (!b_equal)
	{
		if (strcmp(p, szFunName))
		{
			CppTest_TestSuite::nAssertFailFunNum++;
		}
		p = szFunName;
		printf("Assert Failed: File:%s,Line:%d, %s != %s.\n", szFileName, nLineNum, szExpectedName, szActualName);
		ReportPrintf("Assert Failed: File:%s,Line:%d, %s != %s.\n", szFileName, nLineNum, szExpectedName, szActualName);
		LogPrintf("Assert Failed: File:%s,Line:%d, %s != %s.\n", szFileName, nLineNum, szExpectedName, szActualName);
	}
}