#include "stdafx.h"
#include "logprintf.h"

#include "errno.h"

FILE *fp_report = XNULL;
FILE *fp_log = XNULL;
char TagStr[256] = {0};
char LogPath[256] = {0};
char ReportPath[256] = {0};
//将TCHAR转为char  
//该函数映射一个unicode字符串到一个多字节字符串
//*tchar是TCHAR类型指针，*_char是char类型指针   
/**
多字节字符是由一个或多个字节的序列构成的字符。 每个字节序列表示扩展字符集中的单个字符。 多字节字符用于字符集（如日文汉字）中。
宽字符是宽度始终为 16 位的多语言字符代码。 字符常量的类型是 char；对于宽字符，该类型是 wchar_t。 
由于宽字符始终具有固定大小，因此使用宽字符集可以简化使用国际字符集进行的编程。
宽字符串文本 L"hello" 将成为类型为 wchar_t 的六个整数的数组。
{ L'h', L'e', L'l', L'l', L'o', 0 }
Unicode 规范是宽字符的规范。 用于多字节和宽字符之间的转换的运行库例程包括 mbstowcs、mbtowc、wcstombs 和 wctomb。
*/
void WcharToMchar (const TCHAR * tchar, char * _char)  
{  
    int iLenXTh ;  
    //获取字节长度   
    iLenXTh = WideCharToMultiByte(CP_ACP, 0, tchar, -1, XNULL, 0, XNULL, XNULL);  
    //将tchar值赋给_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLenXTh, XNULL, XNULL);   
}

void WcharToInt (const TCHAR * tchar, int * _val)  
{  
    int i;
    int iLenXTh ;  
    char str[256];
    int val = 0;
    //获取字节长度   
    iLenXTh = WideCharToMultiByte(CP_ACP, 0, tchar, -1, XNULL, 0, XNULL, XNULL);  
    //将tchar值赋给_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, str, iLenXTh, XNULL, XNULL);  

    iLenXTh = strlen(str);

    if (iLenXTh > 0) 
    {
        for (i = 0; i < iLenXTh; i++)
        {
            if ((str[i] >= '0') && (str[i] <= '9')) 
            {
                val = val * 10 + (int)str[i] - '0';
            }
            else
            {
                break;
            }
        }
        *_val = val;
    }
    else
    {
        *_val = 0;
    }
}

void GetCurTime(char *szTime, int size)
{
    SYSTEMTIME sysTime;

    GetLocalTime(&sysTime);
    //[21:23:37:005]
#ifdef PLATFORM_WINCE
    sprintf(szTime, "[%02d:%02d:%02d:%03d]", \
        sysTime.wHour, sysTime.wMinute, sysTime.wSecond, \
        sysTime.wMilliseconds);
#else
    sprintf_s(szTime, size, "[%02d:%02d:%02d:%03d]", \
        sysTime.wHour, sysTime.wMinute, sysTime.wSecond, \
        sysTime.wMilliseconds);
#endif
    //sprintf_s(szTime, size, "%04d%02d%02d%02d%02d%02d.txt", \
    //    sysTime.wYear, sysTime.wMonth, sysTime.wDay, \
    //    sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
}

void log_print(FILE *fp, const char *fmt, ...)
{
    char str[256];
    int len;
    va_list args;

    va_start(args, fmt);    

    if (fp != XNULL)
    {
#ifdef PLATFORM_WINCE
        vsprintf(str, fmt, args);
#else
        vsprintf_s(str, 256, fmt, args);
#endif
        len = strlen(str);
        fwrite(str, len, 1, (FILE*)fp);
    }
    else
    {
        vprintf(fmt, args);
    }

    va_end(args);
}

int SetTagStr(Xwchar *szTagStr)
{
    int ret = 1;

    WcharToMchar(szTagStr, TagStr);

    return(ret);
}

int SetLog_Path(Xwchar *path, Xwchar *szLogPathStr)
{
    int ret = 1;
    char str[256] = {0};

    WcharToMchar(szLogPathStr, LogPath);
    WcharToMchar(path, str);
    strcat_s(str, sizeof(str), LogPath);
    printf("log_path:%s\n", str);
    strcpy_s(LogPath, sizeof(LogPath), str);
    return(ret);
}

int SetReport_Path(Xwchar *path, Xwchar *szReportPathStr)
{
    int ret = 1;
    char str[256] = {0};

    WcharToMchar(szReportPathStr, ReportPath);
    WcharToMchar(path, str);
    strcat_s(str, sizeof(str), ReportPath);
    printf("report_path:%s\n", str);
    strcpy_s(ReportPath, sizeof(ReportPath), str);


    return(ret);
}

int OpenLog_Path()
{
    int ret = 1;
	Xwchar *p = XNULL;
	static bool b_LogDirCreat = false;

    if (fp_log == XNULL) 
    {
        printf("open log_path:%s\n", LogPath);
#ifdef PLATFORM_WINCE
        fp_log = fopen(LogPath, "a+");
#else
        fopen_s(&fp_log, LogPath, "a+");
#endif
    }

    if (fp_log == XNULL) 
    {
        printf("fopen log_path failed.\n");
        ret = 0;
    }
	if (!b_LogDirCreat && fp_log != XNULL)
	{
		log_print(fp_log, ("======================================================\n"));
		log_print(fp_log, ("    =           TestSuite\n"));
		log_print(fp_log, ("    =           Build: %s\n"), WIDEN(__TIME__));
		log_print(fp_log, ("    =           Date: [%s]\n"), WIDEN(__DATE__));
		log_print(fp_log, ("======================================================\n"));
		b_LogDirCreat = true;
	}

    return(ret);
}

int OpenReport_Path()
{
    int ret = 1;

    if (fp_report == XNULL) 
    {
        printf("open log_path:%s\n", ReportPath);
#ifdef PLATFORM_WINCE
        fp_report = fopen(ReportPath, "a+");
#else
        fopen_s(&fp_report, ReportPath, "a+");
#endif
    }

    if (fp_report == XNULL) 
    {
        printf("fopen log_path failed.\n");
        ret = 0;
    }

    return(ret);
}

void Close_ReportFile()
{
    if (fp_report != XNULL) 
    {
        fclose(fp_report);
        fp_report = XNULL;
    }
}

void Close_LogFile()
{
    if (fp_log != XNULL) 
    {
        fclose(fp_log);
        fp_log = XNULL;
    }
}


void  ReportbyGlogOn(Xwchar *str)
{
#ifdef GLOG_ON
    char strtmp[256];
    char sztime[20];

    OpenReport_Path();
    GetCurTime(sztime, sizeof(sztime));
    WcharToMchar((TCHAR *)str, strtmp);
    log_print(fp_report, "%s I : %s : %s", sztime, TagStr, strtmp);
	Close_ReportFile();
#endif
}

void  GReportPrintf(Xwchar *str)
{
    char strtmp[256];
    char sztime[20];

    OpenReport_Path();
    GetCurTime(sztime, sizeof(sztime));
    WcharToMchar((TCHAR *)str, strtmp);
    log_print(fp_report, "%s", strtmp);
	Close_ReportFile();
}

void  ReportPrintf(const char *fmt, ...)
{
	char str[256];
	int len;
	va_list args;

	OpenReport_Path();

	va_start(args, fmt);    

	if (fp_report != XNULL)
	{
#ifdef PLATFORM_WINCE
		vsprintf(str, fmt, args);
#else
		vsprintf_s(str, 256, fmt, args);
#endif
		len = strlen(str);
		fwrite(str, len, 1, (FILE*)fp_report);
	}
	else
	{
		vprintf(fmt, args);
	}

	va_end(args);
	Close_ReportFile();
}

void  LogPrintf(const char *fmt, ...)
{
	char str[256];
	int len;
	va_list args;

    OpenLog_Path();

	va_start(args, fmt);    

	if (fp_log != XNULL)
	{
#ifdef PLATFORM_WINCE
		vsprintf(str, fmt, args);
#else
		vsprintf_s(str, 256, fmt, args);
#endif
		len = strlen(str);
		fwrite(str, len, 1, (FILE*)fp_log);
	}
	else
	{
		vprintf(fmt, args);
	}

	va_end(args);
	Close_LogFile();
}

void  GLogPrintf(Xwchar *str)
{
	char strtmp[256];
	char sztime[20];

	OpenLog_Path();
	GetCurTime(sztime, sizeof(sztime));
	WcharToMchar((TCHAR *)str, strtmp);
	//log_print(fp_log, "%s I : %s : %s", sztime, TagStr, strtmp);
	log_print(fp_log, "%s", strtmp);
	Close_LogFile();
}