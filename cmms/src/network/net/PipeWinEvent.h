#pragma once
#include <string>
#include "network/net/Event.h"
#include "network/net/socket.h"
#include <memory>
//����windowsû�йܵ�fd�ĸ����ʱ����socket����

namespace cmms {
	class PipeWinEvent :public Event
	{
	public:
		PipeWinEvent(EventLoop *loop, int start);
		~PipeWinEvent();

		void OnRead() override;
		void OnWrite()override;
		void OnClose() override;
		void OnError(const std::string& msg) override;
		void Write(const char* data, size_t len);

	private:
		struct  sockaddr_in notify_addr_in;
	};
	using PipeWinEventPtr = std::shared_ptr<PipeWinEvent>;
	
}


