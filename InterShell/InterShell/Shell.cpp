#include <Windows.h>
#include <iostream>
#include <string>
#include <cerrno>
#include <sstream>
#include <fstream>
#include "Shell.h"
#include "Utils.h"



bool BaseShell::ExecCommand(const std::string& UserInput)
{
	std::string cmd, path;
	std::istringstream Iss(UserInput);
	Iss >> cmd >> path;

	if (cmd.empty())
	{
		DisplayError("no command was specefied");
		return false;
	}
	if (!(cmd == "ls" || cmd == "cat" || cmd == "cd"))
	{
		DisplayError("invalid command");
		return false;
	}
	if (path.empty() && cmd != "ls")
	{
		DisplayError("the specefied command requires a path");
		return false;
	}
	if (cmd == "cd")
		ChangeDirectory(path);
	else if (cmd == "ls")
	{
		ListDirectory(path);
		DisplayCommandResult();
	}
	else
	{
		CatFile(path);
		DisplayCommandResult();
	}

	return true;

}

bool BaseShell::ChangeDirectory(const std::string& TargetPath)
{
	if (TargetPath == "..")
	{
		DisplayError("terminal does not support usage of .. yet");
		return false;
	}

	const std::string FullPath = GetFullPath(TargetPath, m_CurrWorkingDirectory);
	if (std::filesystem::exists(FullPath) && std::filesystem::is_directory(FullPath))
	{
		m_CurrWorkingDirectory = FullPath;
		DisplayCurrentWorkingDirectory();
		return true;
	}

	DisplayError("invalid path or directory");
	return false;

}

bool BaseShell::ListDirectory(const std::string& TargetPath)
{

	std::wstring DirList;
	const std::string FullPath = GetFullPath(TargetPath, m_CurrWorkingDirectory);
	if (std::filesystem::exists(FullPath) && std::filesystem::is_directory(FullPath))
	{
		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(FullPath))
				DirList += entry.path().filename().wstring() + L"\n";

			std::string NonUnicodeDirList(DirList.begin(), DirList.end());
			m_LastCommandResult = NonUnicodeDirList;
			return true;
		} catch (const std::filesystem::filesystem_error& e) {
			std::string err = e.what();
			m_LastCommandResult = "error executing command " + err;
			return false;
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			m_LastCommandResult = "error executing command " + err;
			return false;
		}
		catch (...) {
			m_LastCommandResult  = "command failed unexpectedly";
			return false;
		}
	}
	m_LastCommandResult = "invalid path or directory";
	return false;
}

bool BaseShell::CatFile(const std::string& TargetPath)
{
	const std::string FullPath = GetFullPath(TargetPath, m_CurrWorkingDirectory);
	if (std::filesystem::exists(FullPath) && std::filesystem::is_regular_file(FullPath))
	{
		try
		{
			std::ifstream file(FullPath, std::ios::binary);
			if (!file) {
				m_LastCommandResult = "failed to open file";
				return false;
			}
			std::ostringstream oss;
			oss << file.rdbuf();
			m_LastCommandResult = oss.str();
			return true;

		} catch (const std::exception& e) {
			std::string err = e.what();
			m_LastCommandResult = "failed executing command " + err;
			return false;
		}
	}

	m_LastCommandResult = "invalid path or file" + FullPath;
	return false;
}

bool RemoteShell::SendCommandResultServer(const std::string& CommandResult)
{
	char ack[4];
	std::string SizeStr = std::to_string(CommandResult.size());
	if(send(m_socket, SizeStr.c_str(), SizeStr.size(), 0) == SOCKET_ERROR)
	{
		return false;
	}

	if(recv(m_socket, ack, sizeof(ack), 0) == SOCKET_ERROR) 
		return false;


	ack[3] = '\0'; 
	if (strcmp(ack, "ACK") != 0) 
		return false;

	if (send(m_socket, CommandResult.c_str(), CommandResult.size(), 0) == SOCKET_ERROR)
		return false;

	return true;
}