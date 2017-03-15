#ifndef	_CPPTEST_TESTSUITE_H__
#define _CPPTEST_TESTSUITE_H__


#include <stdio.h>
#include "exception.h"
#include "timecalc.h"
#include "logprintf.h"

typedef void (*fp)(void);

/**
 * Test suite base class.
 */
class CppTest_TestSuite
{
public:
    /**
     * Called to set up test suite environment.
     */
    virtual void TestSuite_setUp()
    {
    }

    /**
     * Called to clean up test suite environment.
     */
    virtual void TestSuite_tearDown()
    {
    }

	/**
     * Called to set up one test environment.
     */
	virtual void TestCase_StartUp()
	{
	}

	/**
     * Called to clean up one test environment.
     */
	virtual void TestCase_CleanUp()
	{
	}

    virtual ~CppTest_TestSuite()
    {
    }
	static fp *call_slave_ptr;
	static int nAssertFailFunNum;
	static int nOutOfTimeNum;
	static int nExceptNum;
	static int nSuccessNum;
	static HWND hwnd;
	static Xwchar *pszTestDataPath;
	static bool bIsITest;
	bool bTestSuiteJoinCommitTest;
};

void cpptestEqualAssert(bool b_equal, const char *szExpectedName, const char *szActualName, const char *szFileName, const char *szFunName, const int nLineNum);


#define CPPTEST_ASSERT_EQUAL(expected, actual) \
	cpptestEqualAssert(((expected) == (actual)), #expected, #actual, __FILE__, __FUNCTION__, __LINE__);

#define CPP_TESTSUITER(X) \
static int X##cb(int &nTestCaseId, int &nOutOfTimeNum, int &nExceptNum, int &nAssertFailFunNum)


#define CPP_TEST_SUITE(X) \
typedef X ThisTestSuite; \
typedef void (ThisTestSuite::* fpCase)(void);\
typedef struct tagCASEINFO\
{\
	fpCase fpTestCaseFun;\
	const char *pTestCaseName;\
}CASEINFO;\
static CASEINFO g_Case_Table[] = \
{

#define CPP_TEST(F) \
{&ThisTestSuite::F, #F},

#define CPP_TEST_SUITE_END(X) \
};\
void cpptestTestCaseSlave(ThisTestSuite &s, void (ThisTestSuite::*call_slave_ptr)(), const char *szSuiteName, const char *szCaseName)\
{\
	__try {\
	(s.*call_slave_ptr)();\
	} __except(dump_exception()) \
	{\
		s.nExceptNum++;\
		printf(("TestCase: %s::%s has a exception!!!\n"), szSuiteName, szCaseName);\
		ReportPrintf(("TestCase: %s::%s has a exception!!!\n"), szSuiteName, szCaseName);\
		LogPrintf(("TestCase: %s::%s has a exception!!!\n"), szSuiteName, szCaseName);\
	}\
}\
void cpptestTestCase(int &nTestCaseId, ThisTestSuite &s, const char *szSuiteName)\
{\
	int nTime = 0;\
	const char *szCaseName = g_Case_Table[nTestCaseId].pTestCaseName;\
	__try {\
		WASTETIME(int, nTime, 0);\
		s.TestCase_StartUp();\
		cpptestTestCaseSlave(s, g_Case_Table[nTestCaseId].fpTestCaseFun, szSuiteName, szCaseName);\
		s.TestCase_CleanUp();\
		WASTETIME(int, nTime, 1);\
		printf("TestSuite:%s::%s execute. waste time: %0.2fms\n", szSuiteName, szCaseName, nTime/1000.0f);\
		ReportPrintf("TestSuite:%s::%s execute. waste time: %0.2fms\n", szSuiteName, szCaseName, nTime/1000.0f);\
	} __except(dump_exception()) \
	{\
		s.nExceptNum++;\
		printf(("TestCase: %s::%s has a exception in StartUp or CleanUp!!!\n"), szSuiteName, szCaseName);\
		ReportPrintf(("TestCase: %s::%s has a exception in StartUp or CleanUp!!!\n"), szSuiteName, szCaseName);\
		LogPrintf(("TestCase: %s::%s has a exception in StartUp or CleanUp!!!\n"), szSuiteName, szCaseName);\
	}\
}\
int ThisTestSuite::X##cb(int &nTestCaseId, int &nOutOfTimeNum, int &nExceptNum, int &nAssertFailFunNum) \
{\
	const char *szSuiteName = #X;\
	ThisTestSuite s;\
	if ((!bIsITest) && (!s.bTestSuiteJoinCommitTest))\
	{\
		return 0;\
	}\
	if (nTestCaseId == 0)\
	{\
		s.nAssertFailFunNum = 0;\
		s.nOutOfTimeNum = 0;\
		s.nExceptNum = 0;\
		s.nSuccessNum = 0;\
		printf("*****************Suite Test Begin***************\n");\
		ReportPrintf("*****************Suite Test Begin***************\n");\
		printf("Test Suite: %s\n", szSuiteName);\
		ReportPrintf("Test Suite: %s\n", szSuiteName);\
	}\
	if ((nTestCaseId >= 0) && (nTestCaseId < sizeof(g_Case_Table) / sizeof(CASEINFO)))\
	{\
		s.TestSuite_setUp();\
		for (;nTestCaseId < sizeof(g_Case_Table) / sizeof(CASEINFO); nTestCaseId++)\
		{\
			int i = s.nAssertFailFunNum;\
			int j = s.nOutOfTimeNum;\
			int k = s.nExceptNum;\
			cpptestTestCase(nTestCaseId, s, szSuiteName);\
			if (i==s.nAssertFailFunNum && j==s.nOutOfTimeNum && k==s.nExceptNum)\
			{\
				s.nSuccessNum++;\
			}\
		}\
		nTestCaseId--;\
	}\
	if (nTestCaseId < 0)\
	{\
		s.nOutOfTimeNum++;\
		printf("Suite: %s, Case: %s out of time!!!\n", szSuiteName, g_Case_Table[-nTestCaseId - 1].pTestCaseName);\
		ReportPrintf("Suite: %s, Case: %s out of time!!!\n", szSuiteName, g_Case_Table[-nTestCaseId - 1].pTestCaseName);\
		LogPrintf("Suite: %s, Case: %s out of time!!!\n", szSuiteName, g_Case_Table[-nTestCaseId - 1].pTestCaseName);\
	}\
	if ((nTestCaseId < 0) || ((nTestCaseId >= 0) && (nTestCaseId < sizeof(g_Case_Table) / sizeof(CASEINFO))))\
	{\
		s.TestSuite_tearDown();\
	}\
	if (nTestCaseId+1 >= (int)sizeof(g_Case_Table) / (int)sizeof(CASEINFO))\
	{\
		nAssertFailFunNum = s.nAssertFailFunNum;\
		nOutOfTimeNum = s.nOutOfTimeNum;\
		nExceptNum = s.nExceptNum;\
		nTestCaseId = (int)sizeof(g_Case_Table) / (int)sizeof(CASEINFO);\
		printf("AssertFailNum:%d, OutOfTimeNum:%d, ExceptNum:%d\n", s.nAssertFailFunNum, s.nOutOfTimeNum, s.nExceptNum);\
		ReportPrintf("AssertFailNum:%d, OutOfTimeNum:%d, ExceptNum:%d\n", s.nAssertFailFunNum, s.nOutOfTimeNum, s.nExceptNum);\
		printf("*****************Suite Test End*****************\n");\
		ReportPrintf("*****************Suite Test End*****************\n");\
		return (s.nSuccessNum);\
	}\
	return 0;\
}


#endif