#pragma once
#include <vector>


#include <memory>
#include "network/net/Event.h"
#include "network/net/PipeWinEvent.h"
#include "network/net/TimingWheel.h"
#include <unordered_map>
#include <functional>
#include <queue>
#include <mutex>


namespace cmms {

	using EventPtr = std::shared_ptr<Event>;
	using Func = std::function<void()>;

	class EventLoop
	{
	public:
		EventLoop(int index);
		~EventLoop();


		void Loop();
		void Quit();

		void AddEvent(const EventPtr& event);
		void DelEvent(const EventPtr& event);
		bool EnableEventWriting(const EventPtr& event, bool enable);
		bool EnableEventReading(const EventPtr& event, bool enable);

		void AssertInLoopThread();
		bool IsInLoopThread() const;
		
		void RunInLoop(const Func& f);
		void RunInLoop(Func&& f);

		void InsertEntry(uint32_t delay, EntryPtr entryPtr);
		void RunAfter(double delay, const Func& cb);
		void RunAfter(double delay, Func&& cb);

		void RunEvery(double interval, const Func& cb);
		void RunEvery(double interval, Func&& cb);

	private:
		void RunFuctions();
		void QueueInLoop(const Func& f); 
		void WakeUp();
	private:
		bool m_looping = false;
#if defined(_WIN32)	
		HANDLE m_epoll_fd = NULL;
#else
		int m_epoll_fd = -1;
#endif
		std::vector<struct epoll_event> m_epoll_events;
		std::unordered_map<int/*fd*/, EventPtr> m_events;

		std::queue<Func> functions_;
		std::mutex lock_; 

		PipeWinEventPtr pipe_event_;
		int loop_index{-1};
		TimingWheel wheels_;
	};

}


