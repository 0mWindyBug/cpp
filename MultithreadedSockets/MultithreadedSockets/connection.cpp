#include <main.h>

void Connection::print_message(const std::string& message)
{
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "[" << clientName << "]: " << message << std::endl;
}


void Connection::recv_messages()
{
        char buffer[1024];
        while (true) {
            int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) {
                break; // Connection closed or error
            }

            std::string message(buffer, bytesRead);
            print_message(message);
        }

}