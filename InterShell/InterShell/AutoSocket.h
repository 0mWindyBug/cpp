#pragma once
#include <Windows.h>


class AutoSocket
{
public:
	AutoSocket(SOCKET socket) : m_socket(socket) {};
	~AutoSocket() { closesocket(m_socket); WSACleanup(); };

private:
	SOCKET m_socket;
};