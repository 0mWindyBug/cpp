#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstring>
#include <winsock2.h>
#include <connection.h>

#pragma comment(lib, "ws2_32.lib")

extern std::mutex cout_mutex;
