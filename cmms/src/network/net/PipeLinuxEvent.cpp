#include "network/net/EventLoop.h"
#include "network/net/PipeLinuxEvent.h"

namespace cmms {

	PipeLinuxEvent::PipeLinuxEvent(EventLoop* loop)
		:Event(loop)
	{
		int fds[2] = { 0 };
#if defined(LINUX)
		int ret = pipe(fds);
		if (ret < 0)
		{
			std::cout << "create pipe error\n";
			exit(-1);
		}
		m_fd = fds[0];//¶Á
		write_fd = fds[1]; //Ð´
#endif

	}
	PipeLinuxEvent::~PipeLinuxEvent()
	{
		if (m_fd > 0)
		{
			close_socket(m_fd);
			m_fd = -1;
		}

		if (write_fd > 0)
		{
			close_socket(write_fd);
			write_fd = -1;
		}
	}

	void PipeLinuxEvent::OnRead()
	{
#if defined(LINUX)
		int msg = 0;
		if (read(fd, &msg, sizeof(int)) != sizeof(int))
		{
			stf::cout<< "read from pipe error:" << strerror(errno)
				<< ", errno: " << errno << std::endl;

			return;
		}
		std::cout << "+++++++++++++++++OnRead: " << msg << std::endl;
#endif
	}
	void PipeLinuxEvent::OnWrite()
	{

	}
	void PipeLinuxEvent::OnClose()
	{
		if (m_fd > 0)
		{
			close_socket(m_fd);
			m_fd = -1;
		}

		if (write_fd > 0)
		{
			close_socket(write_fd);
			write_fd = -1;
		}

	}
	void PipeLinuxEvent::OnError(const std::string& msg)
	{
		std::cout << "+++++++++++OnError : " << msg << std::endl;
	}
	void PipeLinuxEvent::Write(const char* data, size_t len)
	{
#if defined(LINUX)
		int written = write(write_fd, data, len);
		assert(written == len)
#endif
		return;
	}
}
