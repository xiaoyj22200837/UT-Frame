// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

//#include "targetver.h"
#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

#include <windows.h>


#include <stdio.h>
#include <tchar.h>

#ifdef _WIN32_WCE
#include <altcecrt.h>
#endif

// TODO: 在此处引用程序需要的其他头文件

