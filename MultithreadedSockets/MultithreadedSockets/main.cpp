#include <main.h>

std::mutex cout_mutex;


void handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
        closesocket(clientSocket);
        return;
    }

    std::string clientName(buffer, bytesRead);
    send(clientSocket, "Connection established. Welcome!", 30, 0);

    // create connection object which we are going to recv messages over - returns only when connection is closed. 
    Connection connection(clientSocket, clientName);
    connection.recv_messages();
}

int main()
{
	std::cout << "[*] server is up and running " << std::endl;



    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return -1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Error listening for connections" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Server listening for connections on port 12345..." << std::endl;

    while (true) {
        sockaddr_in clientAddr{};
        int clientLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach(); // Detach the thread to let it run independently , no need to wait on it 
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}