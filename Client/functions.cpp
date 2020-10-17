#include "functions.h"

bool Init()
{
    static WSADATA wsaData;
    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }
    return true;
}

SOCKET CreateSocket()
{
    int iResult = 0;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    SOCKET ConnectSocket = INVALID_SOCKET;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        CleanUp();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            CleanUp();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        CleanUp();
        return 1;
    }
    return ConnectSocket;
}

void Run(SOCKET ConnectSocket)
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

void CloseConnection(SOCKET& ConnectSocket)
{
    closesocket(ConnectSocket);
    CleanUp();
}


bool GetCoordAndClicks(MyPoint& output_p, char& key)
{
    POINT p;
    if (GetCursorPos(&p) == 0)
    {
        return false;
    }
    output_p.x = p.x;
    output_p.y = p.y;
    key = 0;
    if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
    {
        key = 1;
        printf("LBUTTON is pressed \n");
    }
    if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
    {
        key = 2;
        printf("RBUTTON is pressed \n");
    }
    return true;
}

bool SendToServer(SOCKET& ConnectSocket, char* sendbuf, size_t size)
{
    int iResult = 0;
    iResult = send(ConnectSocket, sendbuf, sizeof(MyPoint) + 1, 0);
    if (iResult == SOCKET_ERROR) {
        return false;
    }
    printf("Bytes Sent: %ld\n", iResult);
    return true;
}

void CleanUp()
{
    WSACleanup();
}

size_t FillBuff(char* sendbuf, const MyPoint& mp, char key)
{
    memset(sendbuf, 0, sizeof(sendbuf));
    memcpy(sendbuf, reinterpret_cast<const char*>(&mp), sizeof(MyPoint));
    sendbuf[sizeof(MyPoint)] = key;
    return sizeof(MyPoint) + sizeof(key);
}