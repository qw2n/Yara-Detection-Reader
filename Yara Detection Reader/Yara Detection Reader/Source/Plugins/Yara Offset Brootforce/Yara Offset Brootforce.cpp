#include "Yara Offset Brootforce.h"

#include <iostream>

#include "../../Utils/Process/Process.h"

const uintptr_t BROOT_START = 0x2625A0; // Dont change
const uintptr_t BROOT_END = 0x4C4B40; // Dont change

// Method 1: (results.SCAN_BAD_CERT >= 10 && results.SCAN_BAD_CERT <= 30 && results.SCAN_NEUTRAL >= 80 && results.SCAN_NEUTRAL <= 200 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0)
// Method 2: (results.SCAN_BAD_CERT >= 80 && results.SCAN_BAD_CERT <= 200 && results.SCAN_NEUTRAL >= 10 && results.SCAN_NEUTRAL <= 30 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0)

uintptr_t BrootforceYara(bool logs) {
    int currentOffset = BROOT_START;
    while (currentOffset < BROOT_END) {
        Types::YaraResult results = Process::Memory::Read<Types::YaraResult>(Globals::Base + currentOffset);

        if (logs)
            //std::cout << "[INFO]: Offset: 0x" << std::hex << currentOffset << std::dec << " | Current Point: " << currentOffset << std::endl;

        if (results.SCAN_BAD_CERT >= 10 && results.SCAN_BAD_CERT <= 30 && results.SCAN_NEUTRAL >= 80 && results.SCAN_NEUTRAL <= 200 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0) {
            return currentOffset;
        }

        if (results.SCAN_BAD_CERT >= 80 && results.SCAN_BAD_CERT <= 200 && results.SCAN_NEUTRAL >= 10 && results.SCAN_NEUTRAL <= 30 && results.SCAN_MALICIOUS == 0 && results.SCAN_LIKELY_MALICIOUS == 0 && results.SCAN_SUSPICIOUS == 0) {
            return currentOffset;
        }

        currentOffset += sizeof(int);
    }

    return 0x0;
}

uintptr_t Brootforce::BrootforceYaraOffset(bool logs, bool pause, bool enableTitle) {
	Console::Clear();

	if (enableTitle)
		Console::SetTitle("Yara Offset Brootforce");

	uintptr_t Offset = BrootforceYara(logs);
	if (Offset == 0x0)
        std::cout << "[ERROR]: Failed to dump offset\n";

    Console::Clear();

    if (logs)
        std::cout << "[INFO]: Yara Offset: 0x" << std::hex << std::uppercase << Offset << std::nouppercase << std::dec << " - " << Globals::Version << "\n\n";

    if (pause)
        std::system("pause");

	return Offset;
}