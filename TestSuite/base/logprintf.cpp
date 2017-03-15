#include "stdafx.h"
#include "logprintf.h"

#include "errno.h"

FILE *fp_report = XNULL;
FILE *fp_log = XNULL;
char TagStr[256] = {0};
char LogPath[256] = {0};
char ReportPath[256] = {0};
//��TCHARתΪchar  
//�ú���ӳ��һ��unicode�ַ�����һ�����ֽ��ַ���
//*tchar��TCHAR����ָ�룬*_char��char����ָ��   
/**
���ֽ��ַ�����һ�������ֽڵ����й��ɵ��ַ��� ÿ���ֽ����б�ʾ��չ�ַ����еĵ����ַ��� ���ֽ��ַ������ַ����������ĺ��֣��С�
���ַ��ǿ��ʼ��Ϊ 16 λ�Ķ������ַ����롣 �ַ������������� char�����ڿ��ַ����������� wchar_t�� 
���ڿ��ַ�ʼ�վ��й̶���С�����ʹ�ÿ��ַ������Լ�ʹ�ù����ַ������еı�̡�
���ַ����ı� L"hello" ����Ϊ����Ϊ wchar_t ���������������顣
{ L'h', L'e', L'l', L'l', L'o', 0 }
Unicode �淶�ǿ��ַ��Ĺ淶�� ���ڶ��ֽںͿ��ַ�֮���ת�������п����̰��� mbstowcs��mbtowc��wcstombs �� wctomb��
*/
void WcharToMchar (const TCHAR * tchar, char * _char)  
{  
    int iLenXTh ;  
    //��ȡ�ֽڳ���   
    iLenXTh = WideCharToMultiByte(CP_ACP, 0, tchar, -1, XNULL, 0, XNULL, XNULL);  
    //��tcharֵ����_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLenXTh, XNULL, XNULL);   
}

void WcharToInt (const TCHAR * tchar, int * _val)  
{  
    int i;
    int iLenXTh ;  
    char str[256];
    int val = 0;
    //��ȡ�ֽڳ���   
    iLenXTh = WideCharToMultiByte(CP_ACP, 0, tchar, -1, XNULL, 0, XNULL, XNULL);  
    //��tcharֵ����_char    
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