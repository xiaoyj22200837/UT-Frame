#ifndef	_CPPTEST_TEST_FUN_TESTSUITE_H__
#define _CPPTEST_TEST_FUN_TESTSUITE_H__

#include "CppTest_TestSuite.h"


/**
 * Test suite base class.
 */
class CppTest_TEST_Fun_TestSuite : public CppTest_TestSuite
{
public:
	CppTest_TEST_Fun_TestSuite()
	{
		bTestSuiteJoinCommitTest = true;
	}
    void TestSuite_setUp();
    void TestSuite_tearDown();
	void TestCase_StartUp();
	void TestCase_CleanUp();


	void TestCase_First();

	CPP_TESTSUITER(CppTest_TEST_Fun_TestSuite);
};

#endif