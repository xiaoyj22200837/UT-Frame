#include "stdafx.h"

#include "TestTask.h"
#include "logprintf.h"
#include "CppTest_TestSuite.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Xwchar szDataPath[MAX_PATH];
	Xwchar szTestCasePath[MAX_PATH];
	Xwchar szTestDataPath[MAX_PATH];
	Xwchar szLogPath[MAX_PATH];
	Xwchar szReportPath[MAX_PATH];
	Xwchar szTempPath[MAX_PATH];
	Xwchar szNum[10];
	Xwchar *p;
	Xwchar szTemp[MAX_PATH];
	Xwchar szVersion[260];


	wsprintf(szVersion, XT("TestSuite-V %d.%d.%06d.%04d"), 1, 1, 1, 1);

	if (argc > 1)
	{
		printf("_tmain argc %d\n",argc);
		wcscpy_s(szDataPath, (Xwchar*)argv[1]);
		wcscpy_s(szTestCasePath, (Xwchar*)argv[2]);
		wcscpy_s(szTestDataPath, (Xwchar*)argv[3]);
		wcscpy_s(szReportPath, (Xwchar*)argv[4]);
		wcscpy_s(szLogPath, (Xwchar*)argv[5]);
		wcscpy_s(szTempPath, (Xwchar*)argv[6]);
		wcscpy_s(szNum, (Xwchar*)argv[7]);
		if (szNum[0] == '1')
		{
			SetITest(1);//IT test
		}
		else
		{
			SetITest(2);//Commit test
		}
	}
	else
	{
		wcscpy_s(szTemp, (Xwchar*)argv[0]);
		p = wcsrchr(szTemp, XT('\\'));
		p[0] = 0;
		p = wcsrchr(szTemp, XT('\\'));
		p[0] = 0;
		p = wcsrchr(szTemp, XT('\\'));
		p[1] = 0;
		wsprintf(szDataPath, XT("%sBin\\data\\"), szTemp);
		wsprintf(szTestCasePath, XT("%sBin\\TestCase\\"), szTemp);
		wsprintf(szTestDataPath, XT("%sBin\\TestData\\"), szTemp);
		wsprintf(szReportPath, XT("%sBin\\Report\\"), szTemp);
		wsprintf(szLogPath, XT("%sBin\\Log\\"), szTemp);

		SetITest(2);
	}

#ifdef PLATFORM_WINCE 
	//system("title TrafficTester V1.0"); 
#else 
	//system("title TrafficTester V1.0"); 
	SetConsoleTitle(szVersion); 
#endif    

	SetTagStr(XT("TestSuite")); 
	SetLog_Path(szLogPath, XT("TestSuite.log")); 
	SetReport_Path(szReportPath, XT("TestSuiteReport.txt"));

	GReportPrintf(XT("======================================================\n"));
	wsprintf(szTemp, XT("    =           TestSuite: %s\n"), szVersion);
	GReportPrintf(szTemp);
	wsprintf(szTemp, XT("    =           Build: %s\n"), WIDEN(__TIME__));
	GReportPrintf(szTemp);
	wsprintf(szTemp, XT("    =           Date: [%s]\n"), WIDEN(__DATE__));
	GReportPrintf(szTemp);
	GReportPrintf(XT("======================================================\n"));

	wsprintf(szTemp, XT("DataPath    :%s\n"), szDataPath);
	GReportPrintf(szTemp);
	wsprintf(szTemp, XT("TestCasePath:%s\n"), szTestCasePath);
	GReportPrintf(szTemp);
	wsprintf(szTemp, XT("TestDataPath:%s\n"), szTestDataPath);
	GReportPrintf(szTemp);
	wsprintf(szTemp, XT("ReportPath  :%sTestSuite\\\n"), szReportPath);
	GReportPrintf(szTemp);
	wsprintf(szTemp, XT("LogPath     :%sTestSuite\\\n"), szLogPath);
	GReportPrintf(szTemp);

#ifdef PLATFORM_WINCE
	MEMORYSTATUS s;
	int mem;

	GlobalMemoryStatus(&s);
	mem = s.dwAvailPhys < s.dwAvailVirtual ? s.dwAvailPhys : s.dwAvailVirtual;
	maxTaskNum = (mem - 30 * 1024 * 1024) / (20 * 1024 * 1024) - 1;
#endif

	SetAppPath(szTestDataPath);

	TestTask_Execute();

	printf("执行完毕!\n");

	return 0;
}