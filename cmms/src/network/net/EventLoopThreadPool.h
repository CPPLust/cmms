#pragma once
#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include "base/NonCopyable.h"
#include "network/net/EventLoop.h"
#include "network/net/EventLoopThread.h"


namespace cmms {
	using EventThreadPtr = std::shared_ptr<EventLoopThread>;
	class EventLoopThreadPool :public NonCopyable
	{
	public:
		EventLoopThreadPool(int thread_num, int start = 0, int cpus=4);
		~EventLoopThreadPool();

		std::vector<EventLoop*> GetLoops() const;
		EventLoop* GetNextLoop();
		size_t Size();
		void Start();

	private:
		std::vector<EventThreadPtr> threads_;
		std::atomic_int32_t loop_index_{ 0 };
	};

	
}


