#include "functions.h"

void Run(MY_SOCKET ConnectSocket)
{
    char sendbuf[DEFAULT_BUFLEN];
    char key = 0;
    MyPoint p{};
    size_t buffSize = 0;
    while (true)
    {
        if (false == GetCoordAndClicks(p, key))
        {
            printf("Error: get coordinates and clicks failed");
            continue;
        }
        // Send an initial buffer
        buffSize = FillBuff(sendbuf, p, key);
        if (false == SendToServer(ConnectSocket, sendbuf, buffSize))
        {
            printf("Error: send to server failed");
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    CloseConnection(ConnectSocket);
}


size_t FillBuff(char* sendbuf, const MyPoint& mp, char key)
{
    //memset(sendbuf, 0, sizeof(sendbuf));
    memcpy(sendbuf, reinterpret_cast<const char*>(&mp), sizeof(MyPoint));
    sendbuf[sizeof(MyPoint)] = key;
    return sizeof(MyPoint) + sizeof(key);
}