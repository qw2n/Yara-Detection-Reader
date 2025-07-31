#include "Process.h"

#include <psapi.h>
#include <iostream>
#include <TlHelp32.h>

void Console::Clear() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Console::SetTitle(const char* Title) {
    SetConsoleTitleA(Title);
}

DWORD Process::GetProcessId(const char* processName) {
    HWND hwnd = FindWindowA(NULL, processName);
    if (hwnd) {
        DWORD pid;

        GetWindowThreadProcessId(hwnd, &pid);

        return pid;
    }

    return 0;
}

DWORD Process::WaitProcessId(const char* processName) {
    while (1) {
        DWORD ProcId = Process::GetProcessId(processName);
        if (ProcId != 0) {
            return ProcId;
        }

        Sleep(100);
    }
}

uintptr_t Process::GetModuleBaseAddress(const char* moduleName, DWORD pid) {
    uintptr_t baseAddress = 0;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(snapshot, &moduleEntry)) {
        do {
            if (_stricmp(moduleEntry.szModule, moduleName) == 0) {
                baseAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
                break;
            }
        } while (Module32Next(snapshot, &moduleEntry));
    }

    CloseHandle(snapshot);

    return baseAddress;
}

std::string Process::GetRobloxVersionFromProcess(HANDLE hProcess) {
    char exePath[MAX_PATH];
    if (!GetModuleFileNameExA(hProcess, NULL, exePath, MAX_PATH)) {
        CloseHandle(hProcess);

        return "[ERROR]: Failed to get EXE path";
    }

    std::string path(exePath);

    size_t versionPos = path.find("version-");
    if (versionPos == std::string::npos) {
        return "[ERROR]: Version not found in path";
    }

    size_t endPos = path.find('\\', versionPos);

    return path.substr(versionPos, endPos - versionPos);
}

std::string Process::FeatchOurProgramPath() {
    char path[MAX_PATH];

    GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string exePath(path);

    return exePath.substr(0, exePath.find_last_of("\\/")) + "\\Cache.json";
}