#pragma once
#include <Windows.h>
#include <iostream>

#define SERVER_PORT 998
#define MAX_COMMAND_SIZE 400


void local();
int remote(std::string IpAddress);