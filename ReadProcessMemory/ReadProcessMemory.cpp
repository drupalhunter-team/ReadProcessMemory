// ReadProcessMemory.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#ifdef _DEBUG
#define _PAUSE() system("pause")
#else
#define _PAUSE()
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwProcessId = 4608;	
	DWORD dwErrorCode;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (!hProcess) {
		dwErrorCode = GetLastError();
		printf("OpenProcess failed, error %d(0x%x)\n", dwErrorCode, dwErrorCode);
		_PAUSE();
		return -1;
	}

	HMODULE hModules[1];
	DWORD dwPcbNeeded;
	BOOL bSucceed = EnumProcessModules(hProcess, hModules, sizeof(hModules), &dwPcbNeeded);
	if (!bSucceed) {
		dwErrorCode = GetLastError();
		printf("EnumProcessModules failed, error %d(0x%x)\n", dwErrorCode, dwErrorCode);
		_PAUSE();
		return -1;
	}

	BYTE buffer[4096];
	SIZE_T bytesRead;
	bSucceed = ReadProcessMemory(hProcess, (LPCVOID)hModules[0], (LPVOID)buffer, sizeof(buffer), &bytesRead);
	
	CloseHandle(hProcess);

	_PAUSE();
	return 0;
}

