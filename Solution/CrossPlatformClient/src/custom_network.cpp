#include "custom_network.h"

void CloseConnection(MY_SOCKET& ConnectSocket)
{
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    closesocket(ConnectSocket);
    WSACleanup();
#elif __linux
    close(ConnectSocket);
#endif
}

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
    //For Linux: do nothing
#endif
    return true;
}

MY_SOCKET CreateSocket()
{
    int iResult = 0;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    MY_SOCKET ConnectSocket = INVALID_SOCKET;
    ZeroMemory(&hints, sizeof(hints));
#elif __linux
    MY_SOCKET ConnectSocket;
    memset(&hints, 0, sizeof(hints));
#endif
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        WSACleanup();
#endif
        return INVALID_SOCKET;
    }
    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);

        if (ConnectSocket == INVALID_SOCKET)
        {
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return INVALID_SOCKET;
#elif __linux
            printf("socket() error\n");
            continue;
#endif
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        if (iResult == SOCKET_ERROR)
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
        }
#elif __linux
        if (INVALID_SOCKET == iResult)
        {
            CloseConnection(ConnectSocket);
        }
#endif
        else
        {
            break;
        }
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        WSACleanup();
#endif
        return INVALID_SOCKET;
    }
    return ConnectSocket;
}

bool SendToServer(MY_SOCKET& ConnectSocket, char* sendbuf, size_t size)
{
    int iResult = 0;
    iResult = send(ConnectSocket, sendbuf, size, 0);
    if (iResult == INVALID_SOCKET) {
        return false;
    }
    printf("Bytes Sent: %ld\n", iResult);
    return true;
}