#include "functions.h"


bool Init()
{
    static WSADATA wsaData;
    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
    return true;
}

SOCKET CreateSocket()
{
    int iResult = 0;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    SOCKET listening;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        CleanUp();
    }
    listening = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listening == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        CleanUp();
    }
    iResult = bind(listening, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listening);
        CleanUp();
    }

    freeaddrinfo(result);
    iResult = listen(listening, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listening);
        CleanUp();
    }
    return listening;
}

SOCKET WaitForConnection(SOCKET& ListenSocket)
{
    SOCKET client = accept(ListenSocket, NULL, NULL);
    if (client == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        CleanUp();
    }
    closesocket(ListenSocket);
    return client;
}

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
        SOCKET listeningSocket = CreateSocket();
        if (listeningSocket == INVALID_SOCKET)
            break;
        SOCKET clientSocket = WaitForConnection(listeningSocket);
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

void CleanUp()
{
    WSACleanup();
}
bool GetDataFromClient(SOCKET& clientSocket, MyPoint& output_p, char& key)
{
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult = 0;
    MyPoint* mp = nullptr;
    iResult = recv(clientSocket, recvbuf, recvbuflen, 0);
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
        printf("recv failed with error: %d \n", WSAGetLastError());
        return false;
    }
    return true;
}

void CloseConnection(SOCKET& ConnectSocket)
{
    closesocket(ConnectSocket);
    CleanUp();
}