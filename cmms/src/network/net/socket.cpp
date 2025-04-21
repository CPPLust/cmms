#if !defined(_WIN32)
#include <unistd.h>
#include <arpa/inet.h>
#endif

#include "network/net/socket.h"


#if defined(_WIN32)
#define  close closesocket
#else
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#endif

namespace cmms {


	bool SetNonblocking(int fd)
	{
#ifdef _WIN32
		unsigned long l = 1;
		int n = ioctlsocket(fd, FIONBIO, &l);
		if (n != 0)
		{
			//LogERR("errno = %d reason:%s %d\n", errno, strerror(errno), fd);
			return false;
		}
#else
		int get = fcntl(fd, F_GETFL);
		if (::fcntl(fd, F_SETFL, get | O_NONBLOCK) == -1)
		{
			//LogERR("errno = %d reason:%s %d\n", errno, strerror(errno), fd);
			return false;
		}

		//recv timeout
		struct timeval timeout = { 3, 0 };//3s
		setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
#endif

#ifdef IOS
		int set = 1;
		setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, (void*)&set, sizeof(int));
#endif

		return true;
	}

	int create_udp_server(const char* addr, int port)
	{
		// 1. ����socket
		int sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (-1 == sock) {
			std::cout << "create socket error, errno: " << errno
				<< ", error: " << strerror(errno);
			return -1;
		}


		if (!SetNonblocking(sock))
		{
			//LogERR("Create socket, SetNonblocking fail! error code:%u, discrbie:%s", errno, strerror(errno));
			close_socket(sock);
			return false;
		}



		// 3. ����addr
		struct sockaddr_in sa;
		sa.sin_family = AF_INET;
		sa.sin_port = htons(port);
		sa.sin_addr.s_addr = htonl(INADDR_ANY);

		if (addr && inet_pton(AF_INET, addr, &sa.sin_addr) == 0) {
			std::cout << "invalid address";;
			close_socket(sock);
			return -1;
		}

		// 4. bind
		int ret = bind(sock, (struct sockaddr*)&sa, sizeof(sa));
		if (-1 == ret) {
			std::cout << "bind error, errno: " << errno
				<< ", error: " << strerror(errno);
			close_socket(sock);
			return -1;
		}

		return sock;
	}

	int create_udp_server2(const char* addr, int port)
	{
		int socket = ::socket(AF_INET, SOCK_DGRAM, 0);


		struct sockaddr_in clientaddr;
		clientaddr.sin_family = AF_INET; //��ͥ
		clientaddr.sin_port = htons(port); //�Ƕ�¥¥��
		clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		inet_pton(AF_INET, addr, &clientaddr.sin_addr);

		


		return 0;
	}

}
