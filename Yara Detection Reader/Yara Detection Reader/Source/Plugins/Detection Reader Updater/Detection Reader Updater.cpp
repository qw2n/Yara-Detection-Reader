#include "Detection Reader Updater.h"

#include <fstream>

#include "../../Globals.h"
#include "../../Utils/nlohmann.hpp"
#include "../../Utils/Process/Process.h"

#include "../../Plugins/Yara Offset Brootforce/Yara Offset Brootforce.h"

using json = nlohmann::json;

void ReaderUpdater::Update() {
    Console::Clear();
    Console::SetTitle("Updater");

    std::cout << "[INFO]: Dumping yara offset...\n";

    uintptr_t myOffset = Brootforce::BrootforceYaraOffset(false, false, false);;

    json data;
    data["Yara"] = myOffset;
    
    std::ofstream outFile(Globals::OurProgramPath);
    if (outFile.is_open()) {
        outFile << data.dump(4);
        outFile.close();
    }

    std::cout << "[INFO]: Please Re-Launch Program\n\n";

    std::system("Pause");
}

uintptr_t ReaderUpdater::ReadOffsetFromJson() {
    try {
        std::ifstream file(Globals::OurProgramPath);
        if (!file.is_open()) {
            throw std::runtime_error("File not exist: " + Globals::OurProgramPath);
        }

        nlohmann::json data = nlohmann::json::parse(file);

        if (data["Yara"].is_string()) {
            std::string offsetStr = data["Yara"].get<std::string>();

            if (offsetStr.rfind("0x", 0) == 0) {
                offsetStr = offsetStr.substr(2);
            }

            return std::stoull(offsetStr, nullptr, 16);
        }
        else {
            return data["Yara"].get<uintptr_t>();
        }
    }
    catch (const std::exception& e) {
        std::cout << "[EROR] ReadOffsetFromJson: " << e.what() << std::endl;
        
        return 0;
    }
}