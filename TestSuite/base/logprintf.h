#ifndef GLOGPRINTF_H
#define GLOGPRINTF_H

#include "Xtypes.h"

#define MAX_PATH 260

void  ReportbyGlogOn(Xwchar *str);
void  GReportPrintf(Xwchar *str);
void  ReportPrintf(const char *fmt, ...);
void  GLogPrintf(Xwchar *str);
void  LogPrintf(const char *fmt, ...);

int SetTagStr(Xwchar *szTagStr);
int SetLog_Path(Xwchar *path, Xwchar *szLogPathStr);
int SetReport_Path(Xwchar *path, Xwchar *szReportPathStr);
void Close_LogFile();
void Close_ReportFile();

#endif