#ifndef	_TESTTASK_H__
#define _TESTTASK_H__

#include "Xtypes.h"

#define CPP_REGISTRATION(X) \
{X::X##cb, #X}

typedef int (*fpCbTestSuite)(int &nTestCaseId, int &nOutOfTimeNum, int &nExceptNum, int &nAssertFailFunNum);

typedef struct tagSUITEINFO
{
	fpCbTestSuite fpTestSuiteCbFun;
	const char *pTestSuiteName;
}SUITEINFO;



void TestTask_Execute();

void CALLBACK TimeProc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
LRESULT CALLBACK WindowProc(    
							HWND hwnd,    
							UINT uMsg,    
							WPARAM wParam,    
							LPARAM lParam    
							); 

void SetAppPath(Xwchar *pszTestDataPath);
void CreateWnd();
void DestroyWnd();
void SetITest(int nNum);
void SetTestCaseMaxTime(int nTime);

#endif
