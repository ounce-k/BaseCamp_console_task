#include "custom_network.h"

bool Init()
{
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    static WSADATA wsaData;
    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
#elif __linux
#endif
    return true;
}

MY_SOCKET CreateSocket()
{
    int iResult = 0;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    MY_SOCKET listening;
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    ZeroMemory(&hints, sizeof(hints));
#elif __linux
    memset(&hints, 0, sizeof hints);
#endif
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        WSACleanup();
#endif
        return INVALID_SOCKET;
    }

    listening = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (listening == INVALID_SOCKET)
    {
        freeaddrinfo(result);
        printf("socket failed with error\n");
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        WSACleanup();
#endif
        return INVALID_SOCKET;
    }
    iResult = bind(listening, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == INVALID_SOCKET)
    {
        printf("bind failed with error\n");
        freeaddrinfo(result);
        CloseConnection(listening);
        return INVALID_SOCKET;
    }

    freeaddrinfo(result);
    iResult = listen(listening, SOMAXCONN);
    if (iResult == INVALID_SOCKET)
    {
        printf("listen failed\n");
        CloseConnection(listening);
    }
    return listening;
}

MY_SOCKET WaitForConnection(MY_SOCKET& ListenSocket)
{
    MY_SOCKET client = accept(ListenSocket, NULL, NULL);
    if (client == INVALID_SOCKET) {
        printf("accept failed\n");
        CloseConnection(ListenSocket);
    }
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    closesocket(ListenSocket);
#elif __linux
    CloseConnection(ListenSocket);
#endif
    return client;
}

int request(MY_SOCKET clientSocket, char* recvbuf, int recvbuflen)
{
    return recv(clientSocket, recvbuf, recvbuflen, 0);
}

void CloseConnection(MY_SOCKET& ConnectSocket)
{
    printf("Connection closed\n");
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    closesocket(ConnectSocket);
    WSACleanup();
#elif __linux
    close(ConnectSocket);
#endif
}