#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <Windows.h>
#include <string>


#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return -1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Port number
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    std::string clientName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, clientName);

    // Send the client's name to the server
    send(clientSocket, clientName.c_str(), clientName.size(), 0);

    // Receive the welcome message from the server
    char welcomeMessage[1024];
    recv(clientSocket, welcomeMessage, sizeof(welcomeMessage), 0);
    std::cout << "Server says: " << welcomeMessage << std::endl;

    // Send messages to the server
    std::string message;
    while (true) {
        std::cout << "Enter a message (type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        send(clientSocket, message.c_str(), message.size(), 0);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
