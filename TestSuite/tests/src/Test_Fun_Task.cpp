#include "Test_Fun_Task.h"

#include "TestTask.h"


CPP_TEST_SUITE(CppTest_TEST_Fun_TestSuite)
CPP_TEST(TestCase_First)
CPP_TEST_SUITE_END(CppTest_TEST_Fun_TestSuite);

/**
 * Called to set up test suite environment.
 */
void CppTest_TEST_Fun_TestSuite::TestSuite_setUp()
{
}

/**
 * Called to clean up test suite environment.
 */
void CppTest_TEST_Fun_TestSuite::TestSuite_tearDown()
{
}

/**
 * Called to set up one test environment.
 */
void CppTest_TEST_Fun_TestSuite::TestCase_StartUp()
{
}

/**
 * Called to clean up one test environment.
 */
void CppTest_TEST_Fun_TestSuite::TestCase_CleanUp()
{
}

void CppTest_TEST_Fun_TestSuite::TestCase_First()
{
	MSG msg;
	while(1)
	{
		GetMessage(&msg,XNULL,0,0);
		if(msg.message==WM_TIMER && msg.hwnd == hwnd && msg.wParam < 50)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message==1)
		{
			break;
		}
		break;
	}
}