#ifndef THREAD_H__
#define THREAD_H__

#ifdef __cplusplus
extern "C" 
{
#endif

/**
\defgroup PI_data_structures_group GPI Data Structures
\{
*/

/**
* �߳����ȼ�ö������
* 
*/
typedef enum taXTHREADPRIORITY
{
	eTHREAD_PRIORITY_NORMAL = 0,		/* Ĭ�����ȼ� */
	eTHREAD_PRIORITY_ABOVE_NORMAL,		/* �����ȼ� */
	eTHREAD_PRIORITY_HIGHEST,			/* ������ȼ� */
	eTHREAD_PRIORITY_BELOW_NORMAL,		/* �����ȼ� */
	eTHREAD_PRIORITY_LOWEST				/* ������ȼ� */
} enumTHREADPRIORITY;

/** \} */

/** \addtogroup platform_api_thread_group
\{ */

typedef void* (*THREADPROCFUNC)(void*);	/* �߳�ִ�к������� */

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
void* PI_CreateThread(THREADPROCFUNC threadProcFunc, void *pParam);

/**
**********************************************************************
\brief �˳��߳�
\details �ú������ݴ�����߳̾���˳���Ӧ���̡߳�
\param[in] hThread	�߳̾��
\remarks
\since 
\see 
**********************************************************************/
void PI_DestroyThread(void* hThread);

/**
**********************************************************************
\brief �����߳�
\details �ú������ڹ�������߳̾������Ӧ�̡߳�
\param[in] szThreadName		�߳�����
\remarks
\since 
\see 
**********************************************************************/
void PI_SuspendThread(void* hThread);

/**
**********************************************************************
\brief �ָ��߳�
\details �ú������ڻָ�ִ�д�����߳̾������Ӧ�̡߳�
\param[in] szThreadName		�߳�����
\remarks
\since 
\see 
**********************************************************************/
void PI_ResumeThread(void* hThread);

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
void PI_SetThreadPriority(void* hThread, enumTHREADPRIORITY euPriority);

/* below this line DO NOT add anything */
/** \} */

#ifdef __cplusplus
}
#endif
#endif
