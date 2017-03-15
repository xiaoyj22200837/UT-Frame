#ifndef	_TIME_CALC_H__
#define _TIME_CALC_H__


//return milliseconds
#define WASTETIME(type, nElapseTime, nFlag)	\
{	\
	type nType = (nFlag);	\
	if (nType == 0)	\
	{	\
	(nElapseTime) = (int)GetTickCount();	\
	}	\
	else if (nType == 1)	\
	{	\
	(nElapseTime) = (int)GetTickCount() - (nElapseTime);	\
	}	\
	else \
	{	 \
	\
	}	 \
}

//return milliseconds
#define WASTETIME_HIGHPRECISION(type, nElapseTime, nFlag)	\
{	\
	type nType = (nFlag);	\
	if (nType == 0)	\
	{	\
		LARGE_INTEGER t1;\
		QueryPerformanceCounter(&t1);\
		(nElapseTime) = t1.QuadPart;	\
	}	\
	else if (nType == 1)	\
	{	\
		LARGE_INTEGER t1, tc;\
		QueryPerformanceFrequency(&tc);\
		QueryPerformanceCounter(&t1);\
		(nElapseTime) = (t1.QuadPart - (nElapseTime))*1000.0 / tc.QuadPart;	\
	}	\
	else \
	{	 \
	\
	}	 \
}






#endif