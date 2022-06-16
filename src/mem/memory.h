#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include <initializer_list>

	inline HANDLE hProcess;
	inline uintptr_t moduleBase;
	inline DWORD procId;

	DWORD GetProcId(const wchar_t* procName);

	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);
