#include "thread.h"
#include <windows.h>

/**
**********************************************************************
\brief 创建线程
\details 该函数利用对传入的线程执行函数地址及线程参数创建一个线程。
\param[in] szThreadName		线程名称
\retval 线程句柄
\remarks
\since 
\see 
**********************************************************************/
void* PI_CreateThread(THREADPROCFUNC threadProcFunc, void *pParam)
{
	DWORD dwThreadID = 0u;   /*线程ID*/
	void* hThread = NULL;    /*创建线程返回值*/

	hThread = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)threadProcFunc, pParam, (DWORD)CREATE_SUSPENDED, &dwThreadID);
	
	if (hThread == INVALID_HANDLE_VALUE)
	{

	}
	else
	{
		PI_ResumeThread(hThread);
	}

	return(hThread);
}

/**
**********************************************************************
\brief 退出线程
\details 该函数根据传入的线程句柄退出相应的线程。
\param[in] hThread	线程句柄
\remarks
\since 
\see 
**********************************************************************/
void PI_DestroyThread(void* hThread)
{
	if ((HANDLE)hThread != INVALID_HANDLE_VALUE)
	{
		if (WaitForSingleObject((HANDLE)hThread, 2000u) == WAIT_TIMEOUT )
		{
			TerminateThread((HANDLE)hThread, (DWORD)-1);
		}
		CloseHandle((HANDLE)hThread);
	}
}

/**
**********************************************************************
\brief 挂起线程
\details 该函数用于挂起传入的线程句柄的相应线程。
\param[in] szThreadName		线程名称
\remarks
\since 
\see 
**********************************************************************/
void PI_SuspendThread(void* hThread)
{
	SuspendThread((HANDLE)hThread);
}

/**
**********************************************************************
\brief 恢复线程
\details 该函数用于恢复执行传入的线程句柄的相应线程。
\param[in] szThreadName		线程名称
\remarks
\since 
\see 
**********************************************************************/
void PI_ResumeThread(void* hThread)
{
	ResumeThread((HANDLE)hThread);
}

/**
**********************************************************************
\brief 设置线程优先级
\details 该函数用于设置传入的线程句柄的相应线程的优先级。
\param[in] hThread		线程句柄
\param[in] euPriority	线程优先级
\remarks
\since 
\see 
**********************************************************************/
void PI_SetThreadPriority(void* hThread, enumTHREADPRIORITY euPriority)
{
	int nPriorityValue = 0;	/* 线程优先级 */
	bool bFlag = true;		/* 是否有效优先级 */
	switch (euPriority)
	{
	case eTHREAD_PRIORITY_NORMAL:
	{
		nPriorityValue = THREAD_PRIORITY_NORMAL;
	}
	break;
	case eTHREAD_PRIORITY_ABOVE_NORMAL:
	{
		nPriorityValue = THREAD_PRIORITY_ABOVE_NORMAL;
	}
	break;
	case eTHREAD_PRIORITY_HIGHEST:
	{
		nPriorityValue = THREAD_PRIORITY_HIGHEST;
	}
	break;
	case eTHREAD_PRIORITY_BELOW_NORMAL:
	{
		nPriorityValue = THREAD_PRIORITY_BELOW_NORMAL;
	}
	break;
	case eTHREAD_PRIORITY_LOWEST:
	{
		nPriorityValue = THREAD_PRIORITY_LOWEST;
	}
	break;
	default:
	{/* 其他 */
		bFlag = false;
	}
	break;
	}
	if (bFlag)
	{
		SetThreadPriority((HANDLE)hThread, nPriorityValue);
	}
}
