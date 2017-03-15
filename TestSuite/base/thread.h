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
* 线程优先级枚举类型
* 
*/
typedef enum taXTHREADPRIORITY
{
	eTHREAD_PRIORITY_NORMAL = 0,		/* 默认优先级 */
	eTHREAD_PRIORITY_ABOVE_NORMAL,		/* 高优先级 */
	eTHREAD_PRIORITY_HIGHEST,			/* 最高优先级 */
	eTHREAD_PRIORITY_BELOW_NORMAL,		/* 低优先级 */
	eTHREAD_PRIORITY_LOWEST				/* 最低优先级 */
} enumTHREADPRIORITY;

/** \} */

/** \addtogroup platform_api_thread_group
\{ */

typedef void* (*THREADPROCFUNC)(void*);	/* 线程执行函数类型 */

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
void* PI_CreateThread(THREADPROCFUNC threadProcFunc, void *pParam);

/**
**********************************************************************
\brief 退出线程
\details 该函数根据传入的线程句柄退出相应的线程。
\param[in] hThread	线程句柄
\remarks
\since 
\see 
**********************************************************************/
void PI_DestroyThread(void* hThread);

/**
**********************************************************************
\brief 挂起线程
\details 该函数用于挂起传入的线程句柄的相应线程。
\param[in] szThreadName		线程名称
\remarks
\since 
\see 
**********************************************************************/
void PI_SuspendThread(void* hThread);

/**
**********************************************************************
\brief 恢复线程
\details 该函数用于恢复执行传入的线程句柄的相应线程。
\param[in] szThreadName		线程名称
\remarks
\since 
\see 
**********************************************************************/
void PI_ResumeThread(void* hThread);

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
void PI_SetThreadPriority(void* hThread, enumTHREADPRIORITY euPriority);

/* below this line DO NOT add anything */
/** \} */

#ifdef __cplusplus
}
#endif
#endif
