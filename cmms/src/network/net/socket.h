
#ifndef  __BASE_SOCKET_H_
#define  __BASE_SOCKET_H_

#include<iostream>
#if defined(_WIN32)
#include <WS2tcpip.h>
#include <WinSock2.h>
#else
#include <sys/socket.h>
#include <unistd.h>  //close
#include <netinet/in.h>
#endif

namespace cmms {

class WinsockInitializer {
    public:
        WinsockInitializer() {
#if defined(_WIN32)
            // 初始化Winsock
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                std::cout << "Failed to initialize Winsock";
                exit(1);
            }
#endif
        }

        ~WinsockInitializer() {
#if defined(_WIN32)
            // 清理Winsock
            WSACleanup();
#endif
        }
#if defined(_WIN32)
    private:
        WSADATA wsaData;
#endif
    };

#ifdef _WIN32
typedef int socklen_t;
#define close_socket(x) if (x != INVALID_SOCKET) {::closesocket(x); /*x = INVALID_SOCKET*/;}
#else
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR            (-1)
#define close_socket(x) if (x != INVALID_SOCKET) {::close(x); /*x = INVALID_SOCKET*/;}
#endif

int create_udp_server(const char* addr, int port);
int create_udp_server2(const char* addr, int port);

} // namespace xrtc

#endif  //__BASE_SOCKET_H_


