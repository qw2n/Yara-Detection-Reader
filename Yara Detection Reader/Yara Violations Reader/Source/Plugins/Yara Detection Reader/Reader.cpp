#include "Reader.h"

#include <iostream>

#include "../../Globals.h"
#include "../../../Offsets.h"
#include "../../Utils/Memory/Memory.h"

void Reader::Start(uintptr_t hyperionBase) {
    Console::ClearConsole();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, 30, 6 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    while (true) {
        YaraResult results = Memory::Read<YaraResult>(hyperionBase + Offsets::yaraOffset);
        MoveCursorToTop();

        std::cout << "SCAN_BAD_CERT = " << results.SCAN_BAD_CERT << "          \n";
        std::cout << "SCAN_NEUTRAL = " << results.SCAN_NEUTRAL << "            \n";
        std::cout << "SCAN_SUSPICIOUS = " << results.SCAN_SUSPICIOUS << "      \n";
        std::cout << "SCAN_LIKELY_MALICIOUS = " << results.SCAN_LIKELY_MALICIOUS << "   \n";
        std::cout << "SCAN_MALICIOUS = " << results.SCAN_MALICIOUS << "         \n";

        Sleep(100);
    }
}