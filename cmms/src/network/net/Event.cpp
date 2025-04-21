#include "Event.h"
#include "network/net/EventLoop.h"
#include "network/net/socket.h"
namespace cmms {

	Event::Event(EventLoop* loop)
		:m_loop(loop)
	{
	}
	Event::Event(EventLoop* loop, int fd)
		:m_loop(loop)
		,m_fd(fd)
	{

	}
	Event::~Event()
	{
		if (m_fd > 0)
		{
			close_socket(m_fd);
			m_fd = -1;
		}
	}



	bool Event::EnableWriting(bool enable)
	{
		return m_loop->EnableEventWriting(shared_from_this(), enable);
	}
	bool Event::EnableReading(bool enable)
	{
		return m_loop->EnableEventReading(shared_from_this(), enable);
	}
	int Event::Fd()const 
	{
		return m_fd;
	}


}
