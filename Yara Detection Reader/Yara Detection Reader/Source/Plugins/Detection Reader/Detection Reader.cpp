#include "Detection Reader.h"

#include <iostream>

#include "../../Globals.h"
#include "../../Utils/Process/Process.h"

#include "../../Plugins/Detection Reader Updater/Detection Reader Updater.h"

void MoveCursorToTop(HANDLE hConsole)
{
    COORD cursorPos = { 0, 0 };

    SetConsoleCursorPosition(hConsole, cursorPos);
}

void Reader::Enable() {
    Console::Clear();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, 30, 6 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    Console::SetTitle("Detection Reader");

    const uintptr_t Offset = ReaderUpdater::ReadOffsetFromJson();

    while (1) {
        Types::YaraResult Result = Process::Memory::Read<Types::YaraResult>(Globals::Base + Offset);
        
        MoveCursorToTop(hConsole);

        std::cout << "[INFO]: Current Roblox: " << Globals::Version << "\n\n";

        std::cout << "    [+] SCAN_BAD_CERT = " << Result.SCAN_BAD_CERT << std::endl
            << "    [+] SCAN_NEUTRAL = " << Result.SCAN_NEUTRAL << std::endl
            << "    [+] SCAN_SUSPICIOUS = " << Result.SCAN_SUSPICIOUS << std::endl
            << "    [+] SCAN_LIKELY_MALICIOUS = " << Result.SCAN_LIKELY_MALICIOUS << std::endl
            << "    [+] SCAN_MALICIOUS = " << Result.SCAN_MALICIOUS << std::endl;;

        Sleep(100);
    }
}