#include "Brootforce.h"

#include "../../Globals.h"
#include "../../Utils/Memory/Memory.h"

#include <iostream>

int BROOT_START = 0x2625A0; // Dont change
int BROOT_END = 0x2DC6C0; // Dont change

// Method 1: (results.SCAN_BAD_CERT >= 10 && results.SCAN_BAD_CERT <= 30 && results.SCAN_NEUTRAL >= 80 && results.SCAN_NEUTRAL <= 200 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0)
// Method 2: (results.SCAN_BAD_CERT >= 80 && results.SCAN_BAD_CERT <= 200 && results.SCAN_NEUTRAL >= 10 && results.SCAN_NEUTRAL <= 30 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0)

int PrintResult(uintptr_t currentOffset, int Method) {
    std::cout << "\n";

    std::cout
        << "[FOUND]: Offset: 0x" << std::hex << currentOffset << std::dec
        << " | Current Point: " << currentOffset
        << " | Found by Method " << Method
        << "\n\n";

    std::cout << "Choose:" << "\n1. Continue\n2. Exit\n\n";

    int choose = 0;
    std::cin >> choose;

    return choose;
}

void Brootforce::Start(uintptr_t hyperionBase) {
    Console::ClearConsole();

    int currentOffset = BROOT_START;
    while (currentOffset < BROOT_END) {
        YaraResult results = Memory::Read<YaraResult>(hyperionBase + currentOffset);

        std::cout << "[INFO]: Offset: 0x" << std::hex << currentOffset << std::dec << " | Current Point: " << currentOffset << std::endl;

        if (results.SCAN_BAD_CERT >= 10 && results.SCAN_BAD_CERT <= 30 && results.SCAN_NEUTRAL >= 80 && results.SCAN_NEUTRAL <= 200 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0) {
            int Result = PrintResult(currentOffset, 1);

            if (Result == 2) {
                break;
            }
        }

        if (results.SCAN_BAD_CERT >= 80 && results.SCAN_BAD_CERT <= 200 && results.SCAN_NEUTRAL >= 10 && results.SCAN_NEUTRAL <= 30 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0) {
            int Result = PrintResult(currentOffset, 2);

            if (Result == 2) {
                break;
            }
        }

        currentOffset += sizeof(int);
    }

    Console::ClearConsole();

    std::cout << "\n================ RESULTS ================" << "\n\n";

    std::cout
        << "[INFO]: Current offset: " << std::hex << currentOffset << std::dec
        << " | Last point: " << currentOffset << std::endl;
}