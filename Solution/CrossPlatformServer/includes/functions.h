#pragma once

#include <iostream>
#include <fstream>

#include "custom_network.h"

#define LOG_FILE_NAME "log.txt"

struct MyPoint
{
	int x;
	int y;
};

void Run();
void WriteLogToFile(std::ofstream&, const MyPoint&, char);
bool GetDataFromClient(MY_SOCKET&, MyPoint&, char&);