#include <Windows.h>

#include "../../Globals.h"

namespace Memory {
    template <typename T>
    T Read(uintptr_t address) {
        T buffer{};
        SIZE_T bytesRead;

        if (ReadProcessMemory(Globals::ProcessHandle, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), &bytesRead) &&
            bytesRead == sizeof(T)) {
            return buffer;
        }

        return T();
    }
}

namespace Console {
    void ClearConsole();
}

namespace Process {
    DWORD GetProcessId(const char* processName);
    DWORD WaitProcessId(const char* processName);
    uintptr_t GetModuleBaseAddress(const char* moduleName, DWORD pid);
}