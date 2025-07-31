#pragma once

#include <string>
#include <Windows.h>

namespace Globals {
	inline HANDLE ProcessHandle;

	inline uintptr_t Base;

	inline std::string Version;
	inline std::string OurProgramPath;
}