#include <iostream>
#include <Windows.h>

#include "Source/Globals.h"
#include "Source/Utils/Memory/Memory.h"
#include "Source/Plugins/Yara Detection Reader/Reader.h"
#include "Source/Plugins/Yara Offset Brootforce/Brootforce.h"

int main()
{
    SetConsoleTitle("Yara Detection Reader");

    std::cout << "[INFO]: Waiting Roblox\n";

    DWORD pid = Process::WaitProcessId("Roblox");

    HANDLE h = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    if (!h) {
        std::cerr << "[ERROR]: Failed to open process\n";

        std::cin.get();

        return 0;
    }
    
    uintptr_t hyperionBase = Process::GetModuleBaseAddress("RobloxPlayerBeta.dll", pid);
    if (!hyperionBase) {
        std::cerr << "[ERROR]: Failed to find module base\n";

        std::cin.get();

        return 0;
    }

    Globals::ProcessHandle = h;
    Globals::ProcessId = pid;

    int choose;

    Console::ClearConsole();

    std::cout
        << "    ---> Yara Detection Reader v2 <---\n\n"
        << "        1. Brootforce Yara Offset\n"
        << "        2. Open Yara Detection Reader\n"
        << "\n";

    std::cin >> choose;

    if (choose == 1) {
        Brootforce::Start(hyperionBase);
    }
    else if (choose == 2) {
        Reader::Start(hyperionBase);
    }

    return 0;
}