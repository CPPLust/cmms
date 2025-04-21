#include "network/net/EventLoop.h"
#include "network/net/PipeWinEvent.h"
#include <assert.h>
#include <stdint.h>

namespace cmms {

	PipeWinEvent::PipeWinEvent(EventLoop* loop, int start)
		:Event(loop)
	{
		int port = 18000 + start;
		m_fd = create_udp_server("127.0.0.1", port);
		if (m_fd < 0)
		{
			std::cout << "create udp error: " << strerror(errno)
				<< ", errno: " << errno;
			exit(1);
		}
		notify_addr_in.sin_family = AF_INET;
		inet_pton(AF_INET, "127.0.0.1", &notify_addr_in.sin_addr);
		notify_addr_in.sin_port = htons(port);

	}
	PipeWinEvent::~PipeWinEvent()
	{
		if (m_fd > 0)
		{
			close_socket(m_fd);
			m_fd = -1;
		}
	}

	void PipeWinEvent::OnRead()
	{
		int64_t msg;
#if defined(_WIN32)
		struct  sockaddr_in from;
		socklen_t len = sizeof(from);
		int readlen = ::recvfrom(m_fd, (char*)&msg, sizeof(int64_t), 0, (struct sockaddr*)&from, &len);
		if (readlen != sizeof(int64_t)) {
			std::cout << "read from fd error: " << strerror(errno)
				<< ", errno: " << errno;
			return;
		}
#else
		if (read(fd, &msg, sizeof(int)) != sizeof(int))
		{
			RTC_LOG(LS_WARNING) << "read from pipe error:" << strerror(errno)
				<< ", errno: " << errno;

			return;
		}

#endif
		std::cout << "+++++++++++++++++OnRead: " << msg << std::endl;
	}
	void PipeWinEvent::OnWrite()
	{

	}
	void PipeWinEvent::OnClose()
	{
		if (m_fd > 0)
		{
			close_socket(m_fd);
			m_fd = -1;
		}
	}
	void PipeWinEvent::OnError(const std::string& msg)
	{
		std::cout << "+++++++++++OnError : " << msg << std::endl;
	}
	void PipeWinEvent::Write(const char* data, size_t len)
	{
#if defined(_WIN32)
		int written = ::sendto(m_fd, data, len, 0, (struct sockaddr*)&notify_addr_in, sizeof(notify_addr_in));
		assert(written == len);
#else
		int written = write(_notify_send_fd, &msg, sizeof(int));
		return written == sizeof(int) ? 0 : -1;
#endif
	}
}
