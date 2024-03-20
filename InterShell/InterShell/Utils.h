#pragma once
#include <iostream>
#include <Windows.h>

bool IsRunAsAdmin();
std::string GetProgramDir();
const std::string GetFullPath(const std::string& InputPath, const std::string& BasePath);