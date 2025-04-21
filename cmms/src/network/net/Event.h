#pragma once
#include <string>
#include "network/net/win/wepoll.h"
#include <memory>
namespace cmms {

	//前置声明防止交叉引用
	class EventLoop;
	const  int kEventRead = (EPOLLIN | EPOLLPRI );
	const  int kEventWrite = (EPOLLOUT);
	class Event :public std::enable_shared_from_this<Event>
	{
		friend class EventLoop;
	public:
		Event(EventLoop* loop);
		Event(EventLoop* loop, int fd);
		virtual ~Event();

		virtual void OnRead() {};
		virtual void OnWrite() {};
		virtual void OnClose() {};
		virtual void OnError(const std::string& msg) {};
		bool EnableWriting(bool enable);
		bool EnableReading(bool enable);
		int Fd() const;
	protected:
		EventLoop* m_loop = NULL;
		int m_fd{ -1 };
		int m_event = 0;


	};

}


