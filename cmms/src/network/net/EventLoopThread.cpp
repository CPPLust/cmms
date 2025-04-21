#include "EventLoopThread.h"
#include <iostream>

namespace cmms {

	EventLoopThread::EventLoopThread(int index)
		:thread_([this]() {StartEventLoop();})
		,thread_index(index)
	{
		std::cout << __FUNCTION__ << std::endl;
	}
	EventLoopThread::~EventLoopThread()
	{
		std::cout << __FUNCTION__ << std::endl;
		Run();
		if (loop_)
		{
			loop_->Quit();
		}
		if (thread_.joinable())
		{
			thread_.join();
		}
	}

	void EventLoopThread::Run()
	{
		std::call_once(once_, [this]() {

				{

					std::unique_lock<std::mutex> lk(lock_);
					running_ = true;
					condition_.notify_all();
				}
				auto f = promise_loop.get_future();
				f.get();
			
			});
	}



	EventLoop* EventLoopThread::Loop() const
	{
		return loop_;
	}
	std::thread& EventLoopThread::Thread()
	{
		return thread_;
	}

	void EventLoopThread::StartEventLoop()
	{
		EventLoop loop(thread_index);
		std::unique_lock<std::mutex> lk(lock_);
		condition_.wait(lk, [this]() {return running_;});
		loop_ = &loop;
		promise_loop.set_value(1);
		loop.Loop();
		loop_ = nullptr;

	}



}
