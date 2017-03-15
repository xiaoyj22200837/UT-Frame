#include "stdafx.h"
#include "Test_Fun_Task.h"
#include "thread.h"
#include "timecalc.h"
#include "logprintf.h"
#include "TestTask.h"

static SUITEINFO g_CbTestSuite[] = {\
CPP_REGISTRATION(CppTest_TEST_Fun_TestSuite),
};

static void *uTestSuiteThreadId = 0;
static void *nTestCaseTimerId = 0;

static int g_TestSuiteId = 0;
static int g_TestCaseId = 0;
static int g_TestSuiteIdOld = 0;
static int g_TestCaseIdOld = 0;

static bool g_bSuiteThreadEnd = true;

static int nAssertFailFunNum = 0;
static int nOutOfTimeNum = 0;
static int nExceptNum = 0;

#define TESTCASE_MAX_TIME 5
static int nTestCaseMaxTime = 5;

void* XTestSuiteThread(void* pParam)
{
	static int nTotalTestCaseNum = 0;
	static int nTotalSuccessCaseNum = 0;
	static int nTotalAssertFailFunNum = 0;
	static int nTotalOutOfTimeNum = 0;
	static int nTotalExceptNum = 0;
	int nSuccessCaseNum = 0;
	do
	{
		if (0 != g_CbTestSuite[g_TestSuiteId].fpTestSuiteCbFun)
		{
			CreateWnd();
			__try 
			{
				nSuccessCaseNum = 0;
				nSuccessCaseNum = g_CbTestSuite[g_TestSuiteId].fpTestSuiteCbFun(g_TestCaseId, nOutOfTimeNum, nExceptNum, nAssertFailFunNum);
			} __except(dump_exception()) 
			{
				printf(("TestSuite: %s has a exception in setUp or tearDown!!!\n"),g_CbTestSuite[g_TestSuiteId].pTestSuiteName);
				ReportPrintf(("TestSuite: %s has a exception in setUp or tearDown!!!\n"),g_CbTestSuite[g_TestSuiteId].pTestSuiteName);
				LogPrintf(("TestSuite: %s has a exception in setUp or tearDown!!!\n"),g_CbTestSuite[g_TestSuiteId].pTestSuiteName);
			}
			if (nOutOfTimeNum == 0 && nExceptNum == 0 && nAssertFailFunNum == 0)
			{
				printf(("TestSuite: %s, TotalCaseNum:%d, run OK.\n\n"),g_CbTestSuite[g_TestSuiteId].pTestSuiteName, g_TestCaseId);
				ReportPrintf(("TestSuite: %s, TotalCaseNum:%d, run OK.\n\n"),g_CbTestSuite[g_TestSuiteId].pTestSuiteName, g_TestCaseId);
			}
			else
			{
				printf(("TestSuite: %s, TotalCaseNum:%d, SuccessCaseNum:%d, AssertFailCaseNum:%d, OutOfTimeCaseNum:%d, ExceptCaseNum:%d.\n\n"), \
					g_CbTestSuite[g_TestSuiteId].pTestSuiteName, g_TestCaseId, nSuccessCaseNum, nAssertFailFunNum, nOutOfTimeNum, nExceptNum);
				ReportPrintf(("TestSuite: %s, TotalCaseNum:%d, SuccessCaseNum:%d, AssertFailCaseNum:%d, OutOfTimeCaseNum:%d, ExceptCaseNum:%d.\n\n"), \
					g_CbTestSuite[g_TestSuiteId].pTestSuiteName, g_TestCaseId, nSuccessCaseNum, nAssertFailFunNum, nOutOfTimeNum, nExceptNum);
				LogPrintf(("TestSuite: %s, TotalCaseNum:%d, SuccessCaseNum:%d, AssertFailCaseNum:%d, OutOfTimeCaseNum:%d, ExceptCaseNum:%d.\n\n"), \
					g_CbTestSuite[g_TestSuiteId].pTestSuiteName, g_TestCaseId, nSuccessCaseNum, nAssertFailFunNum, nOutOfTimeNum, nExceptNum);
			}
			nTotalTestCaseNum += g_TestCaseId;
			nTotalSuccessCaseNum += nSuccessCaseNum;
			nTotalAssertFailFunNum += nAssertFailFunNum;
			nTotalOutOfTimeNum += nOutOfTimeNum;
			nTotalExceptNum += nExceptNum;
			g_TestCaseId = 0;
			g_TestSuiteId++;
			nTestCaseMaxTime = TESTCASE_MAX_TIME;
			DestroyWnd();
		}
	} while (g_TestSuiteId < sizeof(g_CbTestSuite) / sizeof(SUITEINFO));

	printf(("\nTotalTestCaseNum: %d, TotalSuccessCaseNum:%d, TotalAssertFailCaseNum:%d, TotalOutOfTimeCaseNum:%d, TotalExceptCaseNum:%d.\n"), \
		nTotalTestCaseNum, nTotalSuccessCaseNum, nTotalAssertFailFunNum, nTotalOutOfTimeNum, nTotalExceptNum);
	ReportPrintf(("\nTotalTestCaseNum: %d, TotalSuccessCaseNum:%d, TotalAssertFailCaseNum:%d, TotalOutOfTimeCaseNum:%d, TotalExceptCaseNum:%d.\n"), \
		nTotalTestCaseNum, nTotalSuccessCaseNum, nTotalAssertFailFunNum, nTotalOutOfTimeNum, nTotalExceptNum);
	if (nTotalAssertFailFunNum > 0 || nTotalOutOfTimeNum > 0 || nTotalExceptNum > 0)
	{
		LogPrintf(("\nTotalTestCaseNum: %d, TotalSuccessCaseNum:%d, TotalAssertFailCaseNum:%d, TotalOutOfTimeCaseNum:%d, TotalExceptCaseNum:%d.\n"), \
			nTotalTestCaseNum, nTotalSuccessCaseNum, nTotalAssertFailFunNum, nTotalOutOfTimeNum, nTotalExceptNum);
	}
	g_bSuiteThreadEnd = false;
	return(XNULL);
}

void* XTestCaseTimerProc(void* pParam)
{
	int nTestCaseTime = 0;
	int temp = 0;

	while(1)
	{
		Sleep(10);
		if (0u != uTestSuiteThreadId)
		{
			if (g_TestSuiteIdOld == g_TestSuiteId && g_TestCaseIdOld == g_TestCaseId)
			{
				if ((nTestCaseMaxTime-1)*100 == nTestCaseTime)
				{
					DestroyWnd();
					PI_DestroyThread(uTestSuiteThreadId);
					printf("XTestCaseTimerProc: out of time PI_DestroyThread :%x\n",uTestSuiteThreadId);
					uTestSuiteThreadId = 0;

					/* out of time, then free the suite data */
					temp = g_TestCaseId + 1;
					g_TestCaseId = -temp;
					if (0 != g_CbTestSuite[g_TestSuiteId].fpTestSuiteCbFun)
					{
						g_CbTestSuite[g_TestSuiteId].fpTestSuiteCbFun(g_TestCaseId, nOutOfTimeNum, nExceptNum, nAssertFailFunNum);
					}
					g_TestCaseId = temp - 1;

					g_TestCaseId++;
					nTestCaseTime = 0;

					uTestSuiteThreadId = PI_CreateThread((THREADPROCFUNC)XTestSuiteThread, XNULL);
					printf("XTestCaseTimerProc PI_CreateThread :%x\n",uTestSuiteThreadId);
					if (0u == uTestSuiteThreadId)
					{
						g_bSuiteThreadEnd = false;
						printf(("XTestCaseTimerProc PI_CreateThread((THREADPROCFUNC)XTestSuiteThread, XNULL) Failed!\n"));
						return(XNULL);
					}
					PI_SetThreadPriority(uTestSuiteThreadId, eTHREAD_PRIORITY_ABOVE_NORMAL);
				}
				nTestCaseTime++;
			}
			else
			{
				nTestCaseTime = 0;
			}
			g_TestSuiteIdOld = g_TestSuiteId;
			g_TestCaseIdOld = g_TestCaseId;
		}
	}
	return(XNULL);
}

void TestTask_Execute()
{
	int nTime = 0;

	WASTETIME(int, nTime, 0);

	nTestCaseTimerId = PI_CreateThread((THREADPROCFUNC)XTestCaseTimerProc, XNULL);
	printf("BLTask_Execute PI_CreateThread :%x\n",nTestCaseTimerId);
	if (0u == nTestCaseTimerId)
	{
		printf(("BLTask_Execute PI_CreateThread((THREADPROCFUNC)XTestCaseTimerProc, XNULL) Failed!\n"));
		return;
	}
	PI_SetThreadPriority(nTestCaseTimerId, eTHREAD_PRIORITY_ABOVE_NORMAL);

	uTestSuiteThreadId = PI_CreateThread((THREADPROCFUNC)XTestSuiteThread, XNULL);
	printf("BLTask_Execute PI_CreateThread :%x\n",uTestSuiteThreadId);
	if (0u == uTestSuiteThreadId)
	{
		PI_DestroyThread(nTestCaseTimerId);
		printf("BLTask_Execute PI_DestroyThread :%x\n",nTestCaseTimerId);
		printf(("BLTask_Execute PI_CreateThread((THREADPROCFUNC)XTestSuiteThread, XNULL) Failed!\n"));
		return;
	}
	PI_SetThreadPriority(uTestSuiteThreadId, eTHREAD_PRIORITY_ABOVE_NORMAL);

	do
	{
	} while (g_bSuiteThreadEnd);

	PI_DestroyThread(uTestSuiteThreadId);
	printf("BLTask_Execute PI_DestroyThread :%x\n",uTestSuiteThreadId);
	uTestSuiteThreadId = 0;

	PI_DestroyThread(nTestCaseTimerId);
	printf("BLTask_Execute PI_DestroyThread :%x\n",nTestCaseTimerId);

	WASTETIME(int, nTime, 1);

	int nms, ns, nmin;
	nms = (int)nTime%1000;
	nTime/=1000;
	ns = (int)nTime%60;
	nTime/=60;
	nmin = (int)nTime;
	printf("All test suites total waste time:%dmin %ds %dms\n", nmin, ns, nms);
	ReportPrintf("All test suites total waste time:%dmin %ds %dms\n", nmin, ns, nms);
}

// 定时器处理函数的实现  
void CALLBACK TimeProc( 
					   HWND hwnd,       
					   UINT message,     
					   UINT idTimer,     
					   DWORD dwTime)
{    
	printf("触发定时器！\n");
}

void SetAppPath(Xwchar *pszTestDataPath)
{
	CppTest_TestSuite::pszTestDataPath = pszTestDataPath;
}

void CreateWnd()
{
	HINSTANCE hInstance;  
	hInstance=GetModuleHandle(XNULL);  
	WNDCLASS Test;  
	Test.cbClsExtra = 0;  
	Test.cbWndExtra = 0;  
	Test.hCursor = LoadCursor(hInstance, IDC_ARROW);
	Test.hIcon = 0;
	Test.lpszMenuName = XNULL;  
	Test.style = CS_HREDRAW | CS_VREDRAW;  
	Test.hbrBackground = (HBRUSH)COLOR_WINDOW;  
	Test.lpfnWndProc = WindowProc;  
	Test.lpszClassName = _T("DTest");  
	Test.hInstance = hInstance;  
	RegisterClass(&Test);  
	HWND hwnd = CreateWindow(    
		_T("DTest"),        //上面注册的类名，要完全一致    
		L"Test",			//窗口标题文字    
		WS_CAPTION,			//窗口外观样式    
		0,					//窗口相对于父级的X坐标    
		0,					//窗口相对于父级的Y坐标    
		800,                //窗口的宽度    
		480,                //窗口的高度    
		XNULL,               //没有父窗口，为XNULL    
		XNULL,               //没有菜单，为XNULL    
		hInstance,          //当前应用程序的实例句柄    
		XNULL);              //没有附加数据，为XNULL 
	if (hwnd == XNULL)
	{
		printf("CreateWindow Failed!!!\n");
	}

#if 0 /* code below should be added to the test case you need to test */
	MSG msg;
	while(1)
	{
		GetMessage(&msg,XNULL,0,0);
		if(msg.message==WM_TIMER)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
#endif

	CppTest_TestSuite::hwnd = hwnd;
}

void DestroyWnd()
{
	DestroyWindow(CppTest_TestSuite::hwnd);
	CppTest_TestSuite::hwnd = XNULL;
}

// 消息处理函数的实现  
LRESULT CALLBACK WindowProc(  
							_In_  HWND hwnd,  
							_In_  UINT uMsg,  
							_In_  WPARAM wParam,  
							_In_  LPARAM lParam  
							)  
{  
	switch(uMsg)  
	{  
	case WM_DESTROY:  
		{  
			PostQuitMessage(0);
			return 0;  
		} 
	}  
	return DefWindowProc(hwnd, uMsg, wParam, lParam);  
}

void SetITest(int nNum)
{
	if (nNum == 1)
	{
		CppTest_TestSuite::bIsITest = true;
	}
	else
	{
		CppTest_TestSuite::bIsITest = false;
	}
}

void SetTestCaseMaxTime(int nTime)
{
	if (nTime < 5 || nTime > 1800)
	{
		return;
	}
	nTestCaseMaxTime = nTime;
}