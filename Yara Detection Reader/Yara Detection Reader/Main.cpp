// By Qwar1e
// Discord < binarycrypt >

#include <iostream>
#include <Windows.h>

#include "Source/Globals.h"
#include "Source/Utils/Process/Process.h"

#include "Source/Plugins/Detection Reader/Detection Reader.h"
#include "Source/Plugins/Yara Offset Brootforce/Yara Offset Brootforce.h"
#include "Source/Plugins/Detection Reader Updater/Detection Reader Updater.h"

int main() {
	Console::SetTitle("Yara Utility");

	std::cout << "[INFO]: Waiting roblox...\n";

	DWORD ProcessId = Process::WaitProcessId("Roblox");

	std::cout << "[INFO]: Open Roblox Process...\n";

	HANDLE Handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, ProcessId);
	if (!Handle) {
		std::cout << "[ERROR]: Cannot open process.\n";

		std::system("pause");

		return 1;
	}

	std::cout << "[INFO]: Featch Roblox Version...\n";

	std::string RobloxVersion = Process::GetRobloxVersionFromProcess(Handle);

	std::cout << "[INFO]: Featch RobloxPlayerBeta.dll...\n";

	uintptr_t Base = Process::GetModuleBaseAddress("RobloxPlayerBeta.dll", ProcessId);
	if (!Base) {
		std::cout << "[ERROR]: Failed to find RobloxPlayerBeta.dll\n";

		std::system("pause");

		return 0;
	}

	std::cout << "[INFO]: Featch our program path...\n";

	Globals::Base = Base;
	Globals::ProcessHandle = Handle;
	Globals::Version = RobloxVersion;
	Globals::OurProgramPath = Process::FeatchOurProgramPath();

	while (1) {
		Console::Clear();

		std::cout << "	-----> Yara Utility <-----\n"
			<< "            + DC: binarycrypt\n\n";

		std::cout << "[1]: Yara Detection Reader\n"
			<< "[2]: Yara Offset Brootforce\n"
			<< "[3]: Update Yara Detection Reader\n\n";

		std::cout << "Choose: ";

		int Plugin;

		std::cin >> Plugin;

		if (Plugin == 1)
			Reader::Enable();

		else if (Plugin == 2)
			Brootforce::BrootforceYaraOffset(true, true, true);

		else if (Plugin == 3)
			ReaderUpdater::Update();

		else continue;

		break;
	}

	return 0;
}