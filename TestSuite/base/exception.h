#ifndef _EXCEPTION_H__
#define _EXCEPTION_H__

#include <windows.h>
#include <tchar.h>

#if defined PLATFORM_WINCE && defined ARM

/* ARMƽ̨�쳣������� */
#include <excpt.h>
extern "C" int __dump_exception(void* except);
#define dump_exception() __dump_exception((void*)GetExceptionInformation())

#else
#define dump_exception() 1
#endif


#endif