#include "Event.h"

#include "network/net/EventLoopThreadPool.h"
#include <windows.h>
#include  <iostream>
namespace cmms {

	void bind_cpu(std::thread& t, int n)
	{
#if defined(_WIN32)
		HANDLE thread_handle = (HANDLE)t.native_handle();
		DWORD_PTR mask= 1ULL << n;

		if (SetThreadAffinityMask(thread_handle, mask) == 0)
		{
			std::cout << "Fail to set thread affinity on windows\n";
		}
#else

#endif
	}

	EventLoopThreadPool::EventLoopThreadPool(int thread_num, int start, int cpus)
	{
		int count_cpus = std::thread::hardware_concurrency();
		if (thread_num <= 0)
		{
			thread_num = 1;
		}

		if (cpus > count_cpus)
		{
			cpus = count_cpus;
		}

		for (int i = 0; i < thread_num;i++)
		{

			threads_.emplace_back(std::make_shared<EventLoopThread>(i+1));
			int n = (start + i) % cpus;
			bind_cpu(threads_.back()->Thread(), n);	
		}
	
	}
	EventLoopThreadPool::~EventLoopThreadPool()
	{

	}

	std::vector<EventLoop*> EventLoopThreadPool::GetLoops() const
	{
		std::vector<EventLoop*> result;
		for (auto& t : threads_)
		{
			result.push_back(t->Loop());
		}
		return result;
	}
	EventLoop* EventLoopThreadPool::GetNextLoop()
	{
		int index = loop_index_;
		loop_index_++;
		return threads_[index % threads_.size()]->Loop();
	}
	size_t EventLoopThreadPool::Size()
	{
		return threads_.size();
	}
	void EventLoopThreadPool::Start()
	{
		for (auto& t : threads_)
		{
			t->Run();
		}
	}
	

}
