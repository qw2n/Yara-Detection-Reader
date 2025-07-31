#pragma once

#include <Windows.h>

#include "../../Globals.h"

namespace Process {
	namespace Memory {
        template <typename T>
        T Read(uintptr_t address) {
            T buffer{};

            SIZE_T bytesRead;

            if (ReadProcessMemory(Globals::ProcessHandle, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), &bytesRead) && bytesRead == sizeof(T))
                return buffer;

            return T();
        }
	}

	DWORD GetProcessId(const char* processName);
	DWORD WaitProcessId(const char* processName);

    std::string FeatchOurProgramPath();
    std::string GetRobloxVersionFromProcess(HANDLE hProcess);

	uintptr_t GetModuleBaseAddress(const char* moduleName, DWORD pid);
}

namespace Console {
	void Clear();
    void SetTitle(const char* Title);
}

namespace Types {
    struct YaraResult {
        int ReaderCount;
        int SCAN_NEUTRAL;
        int SCAN_BAD_CERT;
        int SCAN_MALICIOUS;
        int SCAN_SUSPICIOUS;
        int SCAN_LIKELY_MALICIOUS;
    };
}