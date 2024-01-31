#pragma once
#include <main.h>

class Connection
{
private:
	SOCKET socket;
	std::string clientName;
public:
    Connection(SOCKET socket, const std::string& name) : socket(socket), clientName(name) {}

    ~Connection() {
        closesocket(socket);
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "[" << clientName << "]: Connection closed " << std::endl;
    }
    void recv_messages();
    void print_message(const std::string& message);
};

