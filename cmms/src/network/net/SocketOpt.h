#pragma once
#include <string>
#include "network/net/socket.h"
namespace cmms {

	class SocketOpt {
	public:
		SocketOpt(int sock, bool v6 = false);
		~SocketOpt() = delete;

	private:
		int sock_{ -1 };
		bool is_v6_{ false };

	
	};
	
}


