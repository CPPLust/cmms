#pragma once
#include <string>
#include "network/net/Event.h"
#include "network/net/socket.h"

//由于windows没有管道fd的概念，暂时给个socket试试

namespace cmms {
	class PipeLinuxEvent :public Event
	{
		PipeLinuxEvent(EventLoop *loop);
		~PipeLinuxEvent();

		void OnRead() override;
		void OnWrite()override;
		void OnClose() override;
		void OnError(const std::string& msg) override;
		void Write(const char* data, size_t len);

	private:
		int write_fd{ -1 };
	};
	
}


