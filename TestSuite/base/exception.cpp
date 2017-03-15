#include "exception.h"
#include <tlhelp32.h>
#include "logprintf.h"

#if defined PLATFORM_WINCE && defined ARM

typedef HANDLE (*TCreateToolhelp32Snapshot)( DWORD dwFlags, DWORD th32ProcessID );
typedef BOOL (*TModule32First)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef BOOL (*TModule32Next)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);


int __dump_exception(void* excep)
{
	TCreateToolhelp32Snapshot CreateToolhelp32Snapshot = XNULL;
	TModule32First Module32First = XNULL;
	TModule32Next Module32Next = XNULL;
	HMODULE hToolhelpDll;

	HANDLE hSnapshot;
	BOOL bRet;
	MODULEENTRY32 ModEntry;
	TCHAR szModule[260];
	int i;
	DWORD *sp;
	EXCEPTION_POINTERS* except = (EXCEPTION_POINTERS*)excep;

	Xwchar szStr[512];

	/* output exception base information */
	sprintf(szStr, XT("======================== An Exception Occurred ========================\nExceptionCode    = 0x%08X\nExceptionAddress = 0x%08X\nNumberParameters = %d\n"), \
		except->ExceptionRecord->ExceptionCode, \
		except->ExceptionRecord->ExceptionAddress, \
		except->ExceptionRecord->NumberParameters);
	GLogPrintf(szStr);
	for (i = 0; i < except->ExceptionRecord->NumberParameters; i++)
	{
		sprintf(szStr, XT("      [%d] = 0x%08X\n"), i, except->ExceptionRecord->ExceptionInformation[i]);
		GLogPrintf(szStr);
	}

	/* output context */
#ifdef _ARM_
	sprintf(szStr, XT("----------- Registers -----------\nR0  = 0x%08X\nR1  = 0x%08X\nR2  = 0x%08X\nR3  = 0x%08X\nR4  = 0x%08X\nR5  = 0x%08X\nR6  = 0x%08X\nR7  = 0x%08X\nR8  = 0x%08X\nR9  = 0x%08X\nR10 = 0x%08X\nR11 = 0x%08X\nR12 = 0x%08X\nSp  = 0x%08X\nLr  = 0x%08X\nPc  = 0x%08X\n"), \
		except->ContextRecord->R0, \
		except->ContextRecord->R1, \
		except->ContextRecord->R2, \
		except->ContextRecord->R3, \
		except->ContextRecord->R4, \
		except->ContextRecord->R5, \
		except->ContextRecord->R6, \
		except->ContextRecord->R7, \
		except->ContextRecord->R8, \
		except->ContextRecord->R9, \
		except->ContextRecord->R10, \
		except->ContextRecord->R11, \
		except->ContextRecord->R12, \
		except->ContextRecord->Sp, \
		except->ContextRecord->Lr, \
		except->ContextRecord->Pc);
	GLogPrintf(szStr);
	sp = (DWORD*)except->ContextRecord->Sp;

	/* output stack memory */
	sprintf(szStr, XT("----------- Stacks -----------\n"));
	GLogPrintf(szStr);
	for (i = 0; i < 32; i++)
	{
		sprintf(szStr, XT("[+%04X]    0x%08X\n"), i*4, *sp);
		GLogPrintf(szStr);
		sp++;
	}
#endif

	/* output modules information, because we need it to check where the exception address is. */
	hToolhelpDll = LoadLibrary(XT("toolhelp.dll"));
	if (hToolhelpDll != XNULL)
	{
		/* get the main three functions address */
		CreateToolhelp32Snapshot = (TCreateToolhelp32Snapshot)GetProcAddress(hToolhelpDll, XT("CreateToolhelp32Snapshot"));
		Module32First = (TModule32First)GetProcAddress(hToolhelpDll, XT("Module32First"));
		Module32Next = (TModule32Next)GetProcAddress(hToolhelpDll, XT("Module32Next"));

		if (CreateToolhelp32Snapshot != XNULL && Module32First != XNULL && Module32Next != XNULL)
		{
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
			if (hSnapshot != INVALID_HANDLE_VALUE)
			{
				ModEntry.dwSize = sizeof(MODULEENTRY32);

				bRet = Module32First(hSnapshot, &ModEntry);

				sprintf(szStr, XT("----------- Modules -----------%d\n"), GetLastError());
				GLogPrintf(szStr);
				while (bRet)
				{
					if (hToolhelpDll != ModEntry.hModule)
					{
						if (_tcslen(ModEntry.szExePath) > 0)
							_tcscpy(szModule, ModEntry.szExePath);
						else
							_tcscpy(szModule, ModEntry.szModule);

						sprintf(szStr, XT("BaseAddr = 0x%08X     Size = %8d B     %s\n"), ModEntry.modBaseAddr, ModEntry.modBaseSize, szModule);
						GLogPrintf(szStr);
					}
					bRet = Module32Next(hSnapshot, &ModEntry);
				}

				CloseHandle(hSnapshot);
			}
			else
			{
				sprintf(szStr, XT("CreateToolhelp32Snapshot failed : %d\n"), GetLastError());
				GLogPrintf(szStr);
			}
		}
		else
		{
			sprintf(szStr, XT("GetProcAddress failed : CreateToolhelp32Snapshot = %p, Module32First = %p, Module32Next = %p\n"), CreateToolhelp32Snapshot, Module32First, Module32Next);
			GLogPrintf(szStr);
		}

		/* free library */
		FreeLibrary(hToolhelpDll);
	}
	else
	{
		sprintf(szStr, XT("LoadLibrary failed : %d\n"), GetLastError());
		GLogPrintf(szStr);
	}

	sprintf(szStr, XT("================================= End =================================\n"));
	GLogPrintf(szStr);

	return EXCEPTION_EXECUTE_HANDLER;
}

#else

#endif