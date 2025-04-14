#include "base/TTime.h"
#include <time.h>

#include <iostream>
#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace cmms {

#if defined(_WIN32)
struct timeval {
		long tv_sec;
		long tv_usec;
};
int gettimeofday(struct timeval* tv, void* tz)
{
	//��סtm��ʱ���Ǵ�1900��ʼ����

	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	// �� SYSTEMTIME ת��Ϊ tm �ṹ
	struct tm tm_time = { 0 };
	tm_time.tm_year = sys_time.wYear - 1900; // ��ݣ���1900��ʼ��
	tm_time.tm_mon = sys_time.wMonth - 1;    // �·ݣ�0-11��
	tm_time.tm_mday = sys_time.wDay;          // ��
	tm_time.tm_hour = sys_time.wHour;         // Сʱ
	tm_time.tm_min = sys_time.wMinute;        // ����
	tm_time.tm_sec = sys_time.wSecond;        // ��
	tm_time.tm_isdst = -1;                    // �Ƿ�����ʱ���Զ���⣩


	// �� tm �ṹת��Ϊ time_t��UTC ʱ�䣩
	time_t clock = _mkgmtime(&tm_time); // ʹ�� _mkgmtime ���� UTC ʱ��
	if (clock == (time_t)-1) {
		return -1; // ������
	}


	// ���� timeval �ṹ
	tv->tv_sec = static_cast<long>(clock);
	tv->tv_usec = sys_time.wMilliseconds * 1000L; // ת��Ϊ΢��


	// ������
	std::cout << "Local time (SYSTEMTIME):\n";
	std::cout << sys_time.wYear << "-" << sys_time.wMonth << "-" << sys_time.wDay
		<< " " << sys_time.wHour << ":" << sys_time.wMinute << ":" << sys_time.wSecond << "\n";

	struct tm local_tm;
	localtime_s(&local_tm, &clock); // ��ȫ�汾
	std::cout << "\nVerification (localtime):\n";
	std::cout << local_tm.tm_year + 1900 << "-" << local_tm.tm_mon + 1 << "-" << local_tm.tm_mday
		<< " " << local_tm.tm_hour << ":" << local_tm.tm_min << ":" << local_tm.tm_sec << "\n";

	return 0;
}

#endif


int64_t TTime::NowMS()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0)
		return 0;
	
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
int64_t TTime::Now()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0)
		return 0;

	return tv.tv_sec;
}
int64_t TTime::Now(int& year, int& month, int& day, int& hour, int& minute, int& second)
{
	return 0;
}
std::string TTime::ISOTime()
{
	return 0;
}



}


