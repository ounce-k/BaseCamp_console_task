#pragma once

#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define MY_SOCKET SOCKET
//#define NETWORK_ERROR 1

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#elif __linux

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>

#define INVALID_SOCKET -1
#define MY_SOCKET int
//#define NETWORK_ERROR -1

#endif

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "12345"


bool Init();
MY_SOCKET CreateSocket();
MY_SOCKET WaitForConnection(MY_SOCKET&);
void CloseConnection(MY_SOCKET&);
int request(MY_SOCKET, char*, int);