#include <Windows.h>
#include <filesystem>

bool IsRunAsAdmin()
{
	bool IsAdmin = false;
	HANDLE TokHandle = nullptr;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &TokHandle))
	{
		TOKEN_ELEVATION Elevation;
		DWORD Size = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(TokHandle, TokenElevation, &Elevation, sizeof(Elevation), &Size))
			IsAdmin = Elevation.TokenIsElevated;

		CloseHandle(TokHandle);
	}

	return IsAdmin;
}

std::string GetProgramDir()
{
	return std::filesystem::current_path().string();
}

const std::string GetFullPath(const std::string& InputPath, const std::string& BasePath)
{
	if (std::filesystem::path(InputPath).is_absolute())
		return InputPath;
	
	return BasePath + InputPath;


}

