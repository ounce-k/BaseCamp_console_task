#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "12345"
#define DEFAULT_IP "127.0.0.1"

struct MyPoint
{
	int x;
	int y;
};

bool Init();
SOCKET CreateSocket();
void Run(SOCKET);
void CloseConnection(SOCKET&);
bool GetCoordAndClicks(MyPoint&, char&);
bool SendToServer(SOCKET&, char*, size_t);
void CleanUp();
size_t FillBuff(char*, const MyPoint&, char);