/*
��C/C++����ʱ�����Ƚ�

����Ŀǰ�������Ÿ��ּ�ʱ������һ��Ĵ������ȵ��ü�ʱ���������µ�ǰʱ��tstart��
  Ȼ����һ�γ����ٵ��ü�ʱ���������´�����ʱ��tend����tend��tstart����Ϳ��Եõ������ִ��ʱ�䣬
  ���Ǹ��ּ�ʱ�����ľ��Ȳ�һ��.����Ը��ּ�ʱ��������Щ�򵥼�¼.

	����1,time()��ȡ��ǰ��ϵͳʱ�䣬���صĽ����һ��time_t���ͣ���ʵ����һ����������
	��ֵ��ʾ��CUT��Coordinated Universal Time��ʱ��1970��1��1��00:00:00����ΪUNIXϵͳ��Epochʱ�䣩����ǰʱ�̵�����.

	void test1()
	{
	time_t start,stop;
	start = time(NULL);
	foo();//dosomething
	stop = time(NULL);
	printf("Use Time:%ld\n",(stop-start));
	}

	����2,clock()�������شӡ��������������̡����������е���clock()������ʱ֮���CPUʱ�Ӽ�ʱ��Ԫ��clock tick��������MSDN�г�֮Ϊ����ʱ�䣨wal-clock��

	  ����CLOCKS_PER_SEC����������ʾһ���ӻ��ж��ٸ�ʱ�Ӽ�ʱ��Ԫ

	  void test2()
	  {
	  double dur;
	  clock_t start,end;
	  start = clock();
	  foo();//dosomething
	  end = clock();
	  dur = (double)(end - start);
	  printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
	  }

	  ����3,timeGetTime()�����Ժ���Ƶ�ϵͳʱ�䡣��ʱ��Ϊ��ϵͳ����������������ʱ��,��windows api

	  void test3()
	  {
	  DWORD t1,t2;
	  t1 = timeGetTime();
	  foo();//dosomething
	  t2 = timeGetTime();
	  printf("Use Time:%f\n",(t2-t1)*1.0/1000);
	  }

	  ����4,QueryPerformanceCounter()����������ظ߾�ȷ�����ܼ�������ֵ,��������΢��Ϊ��λ��ʱ.
	  ����QueryPerformanceCounter()ȷ�еľ�ȷ��ʱ����С��λ����ϵͳ�йص�,����,
	  ����Ҫ��ѯϵͳ�Եõ�QueryPerformanceCounter()���ص���������Ƶ��.QueryPerformanceFrequency()�ṩ�����Ƶ��ֵ,����ÿ���������ĸ���.

	  void test4()
	  {
	  LARGE_INTEGER t1,t2,tc;
	  QueryPerformanceFrequency(&tc);
	  QueryPerformanceCounter(&t1);
	  foo();//dosomething
	  QueryPerformanceCounter(&t2);
	  printf("Use Time:%f\n",(t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart);
	  }

	  ����5,GetTickCount���أ�retrieve���Ӳ���ϵͳ������������������elapsed���ĺ����������ķ���ֵ��DWORD

	  void test5()
	  {
	  DWORD t1,t2;
	  t1 = GetTickCount();
	  foo();//dosomething
	  t2 = GetTickCount();
	  printf("Use Time:%f\n",(t2-t1)*1.0/1000);
	  }

	  ����6,RDTSCָ���Intel   Pentium���ϼ����CPU�У���һ����Ϊ��ʱ�����Time   Stamp�����Ĳ�����
	  ����64λ�޷����������ĸ�ʽ����¼����CPU�ϵ�������������ʱ��������������Ŀǰ��CPU��Ƶ���ǳ��ߣ�
	  �������������Դﵽ���뼶�ļ�ʱ���ȡ������ȷ�����������ַ������޷������.��Pentium���ϵ�CPU�У�
	  �ṩ��һ������ָ��RDTSC��Read   Time   Stamp   Counter������ȡ���ʱ��������֣������䱣����EDX:EAX�Ĵ������С�
	  ����EDX:EAX�Ĵ�����ǡ����Win32ƽ̨��C++���Ա��溯������ֵ�ļĴ������������ǿ��԰�����ָ�����һ����ͨ�ĺ������ã�
	  ��ΪRDTSC����C++����Ƕ�����ֱ��֧�֣���������Ҫ��_emitαָ��ֱ��Ƕ���ָ��Ļ�������ʽ0X0F��0X31

	  inline unsigned __int64 GetCycleCount()
	  {
	  __asm
	  {
	  _emit 0x0F;
	  _emit 0x31;
	  }
	  }

	  void test6()
	  {
	  unsigned long t1,t2;
	  t1 = (unsigned long)GetCycleCount();
	  foo();//dosomething
	  t2 = (unsigned long)GetCycleCount();
	  printf("Use Time:%f\n",(t2 - t1)*1.0/FREQUENCY);   //FREQUENCYָCPU��Ƶ��
	  }

	 ����7,gettimeofday() linux�����µļ�ʱ������int gettimeofday ( struct timeval * tv , struct timezone * tz ),
	 gettimeofday()���Ŀǰ��ʱ����tv��ָ�Ľṹ���أ�����ʱ������Ϣ��ŵ�tz��ָ�Ľṹ��.

	//timeval�ṹ����Ϊ:
	struct timeval{
	long tv_sec; ��
long tv_usec; ΢��
};

timezone �ṹ����Ϊ:
struct timezone{
	int tz_minuteswest; ��Greenwich ʱ����˶��ٷ���
	int tz_dsttime; �չ��Լʱ���״̬
};
void test7()
{
	struct timeval t1, t2;
	double timeuse;
	gettimeofday(&t1, NULL);
	foo();
	gettimeofday(&t2, NULL);
	timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	printf("Use Time:%f\n", timeuse);
}

����8, linux�����£���RDTSCָ���ʱ.�뷽��6��һ����.ֻ������linuxʵ�ַ�ʽ�е����.

#if defined (__i386__)
static __inline__ unsigned long long GetCycleCount(void)
{
	unsigned long long int x;
	__asm__ volatile("rdtsc":"=A"(x));
	return x;
}
#elif defined (__x86_64__)
static __inline__ unsigned long long GetCycleCount(void)
{
	unsigned hi, lo;
	__asm__ volatile("rdtsc":"=a"(lo), "=d"(hi));
	return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}
#endif

void test8()
{
	unsigned long t1, t2;
	t1 = (unsigned long)GetCycleCount();
	foo();//dosomething
	t2 = (unsigned long)GetCycleCount();
	printf("Use Time:%f\n", (t2 - t1)*1.0 / FREQUENCY); //FREQUENCY  CPU��Ƶ��
}

�򵥵ıȽϱ������

���	����	����	���ȼ���	ʱ��
1	time	Cϵͳ����	�� < 1s
2	clcok	Cϵͳ����	�� < 10ms
3	timeGetTime	Windows API	�� < 1ms
4	QueryPerformanceCounter	Windows API	�� < 0.1ms
5	GetTickCount	Windows API	�� < 1ms
6	RDTSC	ָ��	�� < 0.1ms
7	gettimeofday 	linux������Cϵͳ����	�� < 0.1ms

�ܽᣬ����1, 2, 7, 8������linux������ִ�У�����1, 2, 3, 4, 5, 6������windows������ִ��.
���У�timeGetTime()��GetTickCount()�ķ���ֵ����ΪDWORD����ͳ�Ƶĺ���������ʱ������ʹ�����0��Ӱ��ͳ�ƽ��.
���Խ����windows�����£���ƵΪ1.6GHz����λΪ��.

1 Use Time : 0
2 Use Time : 0.390000
3 Use Time : 0.388000
4 Use Time : 0.394704
5 Use Time : 0.407000
6 Use Time : 0.398684
linux�����£���ƵΪ2.67GHz����λΪ��

1 Use Time : 1
2 Use Time : 0.290000
7 Use Time : 0.288476
8 Use Time : 0.297843
����time()��ʱ�����ľ��ȱȽϵͣ�������г���ʱ������õ���ͬ�Ľ����ʱ��Ϊ0��ʱ��Ϊ1

foo()�������£�

void foo()
{
	long i;
	for (i = 0; i < 100000000; i++)
	{
		long a = 0;
		a = a + 1;
	}
}
*/