#pragma once
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include "custom_network.h"
#include "mouse_handler.h"


void Run(MY_SOCKET);
size_t FillBuff(char*, const MyPoint&, char);