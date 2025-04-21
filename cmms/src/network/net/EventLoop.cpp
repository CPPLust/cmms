
#include "network/net/EventLoop.h"
#include <iostream>
#include "network/net/socket.h"
#include "base/TTime.h"


namespace cmms {
	static thread_local EventLoop* t_local_eventloop = NULL;
	EventLoop::EventLoop(int index)
		:m_epoll_fd(epoll_create(1024))
		,m_epoll_events(1024)
		, loop_index(index)
	{
		if (t_local_eventloop)
		{
			std::cout << "there already has a eventloop!!!";
			exit(-1);
		}
		t_local_eventloop = this;
	}

	EventLoop::~EventLoop()
	{
		Quit();
	}

	void EventLoop::Loop()
	{
		m_looping = true;
		int64_t timeout = 1000;
		while (m_looping)
		{
			//std::fill(m_epoll_events.begin(), m_epoll_events.end(), 0x00);
			for (auto& event : m_epoll_events) {
				memset(&event, 0, sizeof(struct epoll_event));
			}

			auto ret = epoll_wait(m_epoll_fd, (struct epoll_event*)&m_epoll_events[0]
				, static_cast<int>(m_epoll_events.size()), timeout);
			if (ret >= 0)
			{
				for (int i = 0; i < ret; i++)
				{
					struct epoll_event& ev = m_epoll_events[i];
					if (ev.data.fd <= 0)
					{
						continue;
					}

					auto iter = m_events.find(ev.data.fd);
					if (iter == m_events.end())
					{
						continue;
					}
					EventPtr& event = iter->second;

					if (ev.events & EPOLLERR)
					{
						//接口有没有关闭
						int error = 0;
						socklen_t len = sizeof(error);
						getsockopt(event->Fd(), SOL_SOCKET, SO_ERROR, (char *) & error, &len);
						
						event->OnError(strerror(error));
					}
					else if ((ev.events & EPOLLHUP) && !(ev.events & EPOLLIN))
					{
						//接口有没有挂起并且不是输入  关闭的
						event->OnClose();
					}
					else if (ev.events & (EPOLLIN | EPOLLPRI))
					{
						//输入事件
						event->OnRead();
					}
					else if (ev.events & EPOLLOUT)
					{
						event->OnWrite();
					}
				}

				if (ret == static_cast<int>(m_epoll_events.size()))
				{
					m_epoll_events.resize(m_epoll_events.size() * 2);
				}
				RunFuctions();
				int64_t now = TTime::NowMS();
				wheels_.OnTimer(now);
			}
			//else if (0 == ret)
			//{
			//	//timeout
			//}
			else if (ret < 0)
			{
				//出错了
				std::cout << "epoll wait error" << std::endl;
			}


		}
	}

	void EventLoop::Quit()
	{
		m_looping = false;
	}

	void EventLoop::AddEvent(const EventPtr& event)
	{
		auto iter = m_events.find(event->Fd());
		if (iter != m_events.end())
		{
			return;
		}

		event->m_event |= kEventRead;

		m_events[event->Fd()] =  event;

		struct epoll_event ev;
		ev.events = event->m_event;
		ev.data.fd = event->m_fd;

		epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, event->m_fd, &ev);
	}
	void EventLoop::DelEvent(const EventPtr& event)
	{
		auto iter = m_events.find(event->Fd());
		if (iter == m_events.end())
		{
			return;
		}
		m_events.erase(iter);


		struct epoll_event ev;
		ev.events = event->m_event;
		ev.data.fd = event->m_fd;

		epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, event->m_fd, &ev);
	}
	bool EventLoop::EnableEventWriting(const EventPtr& event, bool enable)
	{
		auto iter = m_events.find(event->Fd());
		if (iter == m_events.end())
		{
			std::cout << "cannot find event fd:" << event->Fd();
			return false;
		}

		if (enable)
		{
			event->m_event |= kEventWrite;
		}
		else
		{
			event->m_event &= ~kEventWrite;
		}


		struct epoll_event ev;
		ev.events = event->m_event;
		ev.data.fd = event->m_fd;

		epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, event->m_fd, &ev);


		return true;
	}
	bool EventLoop::EnableEventReading(const EventPtr& event, bool enable)
	{
		auto iter = m_events.find(event->Fd());
		if (iter == m_events.end())
		{
			std::cout << "cannot find event fd:" << event->Fd();
			return false;
		}

		if (enable)
		{
			event->m_event |= kEventRead;
		}
		else
		{
			event->m_event &= ~kEventRead;
		}


		struct epoll_event ev;
		ev.events = event->m_event;
		ev.data.fd = event->m_fd;

		epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, event->m_fd, &ev);
		return true;
	}



	void EventLoop::AssertInLoopThread()
	{
		if (!IsInLoopThread())
		{
			std::cout << "forbiden to run on other thread\n";
			exit(-1);
		}

	}
	bool EventLoop::IsInLoopThread() const
	{
		return t_local_eventloop == this; 
	}

	void EventLoop::RunInLoop(const Func& f)
	{
		if (IsInLoopThread())
		{
			f();
		}
		else
		{
			std::lock_guard<std::mutex> lk(lock_);
			functions_.push(f);
			WakeUp();
		}	
	}
	void EventLoop::RunInLoop(Func&& f)
	{
		if (IsInLoopThread())
		{
			f();
		} 
		else
		{
			std::lock_guard<std::mutex> lk(lock_);
			functions_.push(std::move(f));

			WakeUp();
		}
	}


	void EventLoop::RunFuctions()
	{
		std::lock_guard<std::mutex> lk(lock_);
		while (!functions_.empty())
		{
			auto& f = functions_.front();
			f();
			functions_.pop();
		}

	}
	void EventLoop::QueueInLoop(const Func& f)
	{

	}

	void EventLoop::WakeUp()
	{
		if (!pipe_event_)
		{
			pipe_event_ = std::make_shared<PipeWinEvent>(this,loop_index);
			AddEvent(pipe_event_);
		}
		int64_t tmp = 1;
		pipe_event_->Write((const char*)&tmp, sizeof(tmp));
	}

	void EventLoop::InsertEntry(uint32_t delay, EntryPtr entryPtr)
	{
		if (IsInLoopThread())
		{
			wheels_.InsertEntry(delay, entryPtr);
		}
		else
		{
			RunInLoop([this, delay, entryPtr]() {
				wheels_.InsertEntry(delay, entryPtr);

				});
		}
	}
	void EventLoop::RunAfter(double delay, const Func& cb)
	{
		if (IsInLoopThread())
		{
			wheels_.RunAfter(delay, cb);
		}
		else
		{
			RunInLoop([this, delay, cb]() {
				wheels_.RunAfter(delay, cb);

				});
		}
	}
	void EventLoop::RunAfter(double delay, Func&& cb)
	{
		if (IsInLoopThread())
		{
			wheels_.RunAfter(delay, cb);
		}
		else
		{
			RunInLoop([this, delay, cb]() {
				wheels_.RunAfter(delay, cb);

				});
		}
	}

	void EventLoop::RunEvery(double interval, const Func& cb)
	{
		if (IsInLoopThread())
		{
			wheels_.RunEvery(interval, cb);
		}
		else
		{
			RunInLoop([this, interval, cb]() {
				wheels_.RunEvery(interval, cb);

				});
		}
	}
	void EventLoop::RunEvery(double interval, Func&& cb)
	{
		if (IsInLoopThread())
		{
			wheels_.RunEvery(interval, cb);
		}
		else
		{
			RunInLoop([this, interval, cb]() {
				wheels_.RunEvery(interval, cb);

				});
		}
	}
}
