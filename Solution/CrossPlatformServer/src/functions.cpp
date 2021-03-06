#include "functions.h"

void Run()
{
    char key = 0;
    MyPoint p{};
    std::ofstream LogFile(LOG_FILE_NAME);
    if (!LogFile.is_open())
    {
        printf("Error: open file %s failed", LOG_FILE_NAME);
        return;
    }
    while (true)
    {
        MY_SOCKET listeningSocket = CreateSocket();
        if (listeningSocket == INVALID_SOCKET)
            break;
        MY_SOCKET clientSocket = WaitForConnection(listeningSocket);
        if (clientSocket != INVALID_SOCKET)
        {
            // Receive until the peer shuts down the connection
            do {
                if (false == GetDataFromClient(clientSocket, p, key))
                {
                    break;
                }
                WriteLogToFile(LogFile, p, key);
            } while (true);

            CloseConnection(clientSocket);
        }
    }
    LogFile.close();
}

void WriteLogToFile(std::ofstream& file, const MyPoint& p, char key)
{
    file << p.x << "x" << p.y;
    switch (key)
    {
    case 0:
        break;
    case 1:
        file << " LMK (Left Mouse Click)";
        break;
    case 2:
        file << " RMK (Right Mouse Click)";
        break;
    default:
        file << " Unknown key";
    }
    file << std::endl;
}


bool GetDataFromClient(MY_SOCKET& clientSocket, MyPoint& output_p, char& key)
{
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult = 0;
    MyPoint* mp = nullptr;
    iResult = request(clientSocket, recvbuf, recvbuflen);
    if (iResult > 0) {
        if (iResult != sizeof(MyPoint) + 1)
        {
            printf("Eror: invalid data size: %d \n", iResult);
            return false;
        }
        mp = reinterpret_cast<MyPoint*>(recvbuf);
        output_p.x = mp->x;
        output_p.y = mp->y;
        key = recvbuf[sizeof(MyPoint)];
        printf("x = %d, y = %d, key = %d \n", output_p.x, output_p.y, key);
    }
    else if (iResult == 0) {
        printf("Connection closing... \n");
        return false;
    }
    else {
        printf("recv failed with error \n");
        return false;
    }
    return true;
}
