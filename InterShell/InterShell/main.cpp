#include <iostream>
#include <Windows.h>
#include <string>
#include "Shell.h"





int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "[*] Usage : " << argv[0] << "<Local / Remote > [ip address] " << std::endl;
		return -1;
	}

	std::string mode = argv[1];
	if (mode == "Local")
	{
		std::cout << "[*] interactive shell operating in local mode" << std::endl;
	}
	else if (mode == "Remote" && argc == 3)
	{
		std::string IpAddress = argv[2];
		std::cout << "[*] interactive shell operating in remote mode with " << IpAddress << std::endl;
	}
	else
	{
		std::cerr << "[*] Invalid Usage..." << std::endl;
		return -1;
	}

	std::string UserInput; 

	LocalShell shell;

	while (true)
	{
		std::getline(std::cin, UserInput);
		shell.ExecCommand(UserInput);
	}



	return 0; 
}