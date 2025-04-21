
#include "network/net/EventLoopThread.h"
#include "network/net/EventLoopThreadPool.h"
#include "network/net/InetAddress.h"
#include <iostream>
#include <thread>
#include "base/TTime.h"
#include <stdint.h>
using namespace cmms;





int main(int argc, char* argv[])
{

	std::string host;
	while (std::cin >> host)
	{
		InetAddress addr(host);
		std::cout << "host: " << host << std::endl
			<< "ip: " << addr.IP() << std::endl
			<< "port: " << addr.Port() << std::endl
			<< "lan: " << addr.IsLanIp() << std::endl
			<< "wan: " << addr.IsWanIp() << std::endl
			<< "loop: " << addr.IsLoopbackIp() << std::endl;
			
	}



	getchar();
	return 0;
}
