#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "12345"
#define LOG_FILE_NAME "log.txt"

struct MyPoint
{
	int x;
	int y;
};



bool Init();
SOCKET CreateSocket();
SOCKET WaitForConnection(SOCKET&);
void Run();
void WriteLogToFile(std::ofstream&, const MyPoint&, char);
void CleanUp();
bool GetDataFromClient(SOCKET&, MyPoint&, char&);
void CloseConnection(SOCKET&);