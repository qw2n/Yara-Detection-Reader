#pragma once

#include <Windows.h>

struct YaraResult {
    int ReaderCount;
    int SCAN_NEUTRAL;
    int SCAN_BAD_CERT;
    int SCAN_MALICIOUS;
    int SCAN_SUSPICIOUS;
    int SCAN_LIKELY_MALICIOUS;
};

inline void MoveCursorToTop()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = { 0, 0 };

    SetConsoleCursorPosition(hConsole, cursorPos);
}

namespace Globals {
    inline DWORD ProcessId = NULL;
    inline HANDLE ProcessHandle = INVALID_HANDLE_VALUE;
}