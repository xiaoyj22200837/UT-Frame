#include "thread.h"
#include <windows.h>

/**
**********************************************************************
\brief �����߳�
\details �ú������öԴ�����߳�ִ�к�����ַ���̲߳�������һ���̡߳�
\param[in] szThreadName		�߳�����
\retval �߳̾��
\remarks
\since 
\see 
**********************************************************************/
void* PI_CreateThread(THREADPROCFUNC threadProcFunc, void *pParam)
{
	DWORD dwThreadID = 0u;   /*�߳�ID*/
	void* hThread = NULL;    /*�����̷߳���ֵ*/

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
\brief �˳��߳�
\details �ú������ݴ�����߳̾���˳���Ӧ���̡߳�
\param[in] hThread	�߳̾��
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
\brief �����߳�
\details �ú������ڹ�������߳̾������Ӧ�̡߳�
\param[in] szThreadName		�߳�����
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
\brief �ָ��߳�
\details �ú������ڻָ�ִ�д�����߳̾������Ӧ�̡߳�
\param[in] szThreadName		�߳�����
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
\brief �����߳����ȼ�
\details �ú����������ô�����߳̾������Ӧ�̵߳����ȼ���
\param[in] hThread		�߳̾��
\param[in] euPriority	�߳����ȼ�
\remarks
\since 
\see 
**********************************************************************/
void PI_SetThreadPriority(void* hThread, enumTHREADPRIORITY euPriority)
{
	int nPriorityValue = 0;	/* �߳����ȼ� */
	bool bFlag = true;		/* �Ƿ���Ч���ȼ� */
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
	{/* ���� */
		bFlag = false;
	}
	break;
	}
	if (bFlag)
	{
		SetThreadPriority((HANDLE)hThread, nPriorityValue);
	}
}
