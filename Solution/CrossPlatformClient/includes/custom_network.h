#pragma once
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define MY_SOCKET SOCKET
#define NETWORK_ERROR 1

#elif __linux

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MY_SOCKET int
#define INVALID_SOCKET -1
#define NETWORK_ERROR -1

#endif

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "12345"
#define DEFAULT_IP "127.0.0.1"

bool Init();
MY_SOCKET CreateSocket();
void CloseConnection(MY_SOCKET&);
bool SendToServer(MY_SOCKET&, char*, size_t);