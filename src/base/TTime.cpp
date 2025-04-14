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
	//记住tm的时间是从1900开始计算

	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	// 将 SYSTEMTIME 转换为 tm 结构
	struct tm tm_time = { 0 };
	tm_time.tm_year = sys_time.wYear - 1900; // 年份（从1900开始）
	tm_time.tm_mon = sys_time.wMonth - 1;    // 月份（0-11）
	tm_time.tm_mday = sys_time.wDay;          // 日
	tm_time.tm_hour = sys_time.wHour;         // 小时
	tm_time.tm_min = sys_time.wMinute;        // 分钟
	tm_time.tm_sec = sys_time.wSecond;        // 秒
	tm_time.tm_isdst = -1;                    // 是否夏令时（自动检测）


	// 将 tm 结构转换为 time_t（UTC 时间）
	time_t clock = _mkgmtime(&tm_time); // 使用 _mkgmtime 处理 UTC 时间
	if (clock == (time_t)-1) {
		return -1; // 错误处理
	}


	// 设置 timeval 结构
	tv->tv_sec = static_cast<long>(clock);
	tv->tv_usec = sys_time.wMilliseconds * 1000L; // 转换为微秒


	// 输出结果
	std::cout << "Local time (SYSTEMTIME):\n";
	std::cout << sys_time.wYear << "-" << sys_time.wMonth << "-" << sys_time.wDay
		<< " " << sys_time.wHour << ":" << sys_time.wMinute << ":" << sys_time.wSecond << "\n";

	struct tm local_tm;
	localtime_s(&local_tm, &clock); // 安全版本
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


