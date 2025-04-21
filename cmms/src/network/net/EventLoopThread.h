#pragma once
#include "base/NonCopyable.h"
#include "network/net/EventLoop.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
namespace cmms {

	class EventLoopThread:public NonCopyable
	{
	public:
		EventLoopThread(int index);
		~EventLoopThread();

		void Run();


		
		EventLoop* Loop() const;

		std::thread& Thread();

	private:
		void StartEventLoop();


		EventLoop* loop_{nullptr};
		std::thread thread_;
		bool running_{ false };

		std::mutex lock_;
		std::condition_variable condition_;
		
		//多线程保证只执行一次
		std::once_flag once_;

		std::promise<int> promise_loop;
		int thread_index;



	};
}


