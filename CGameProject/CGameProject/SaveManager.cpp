#include "SaveManager.h"
#include "Creature.h"
#include "json.hpp"

#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;
using json = nlohmann::json;

SaveManager::SaveManager() {

    std::ifstream textFile("json/SaveManager.json");
    if (!textFile.is_open()) {
        std::cerr << "Failed to load save_text.json\n";
        exit(1);
    }
    textFile >> text;

    const std::string saveDirectory = "saves";
    if (!fs::exists(saveDirectory)) {
        fs::create_directory(saveDirectory);
    }

    std::vector<fs::path> saveFiles;
    for (const auto& entry : fs::directory_iterator(saveDirectory)) {
        if (entry.path().extension() == ".json") {
            saveFiles.push_back(entry.path());
        }
    }

    std::cout << text["AvailableSaves"] << "\n";
    for (size_t i = 0; i < saveFiles.size(); ++i) {
        std::cout << i + 1 << ". " << saveFiles[i].filename().string() << '\n';
    }

    std::cout << saveFiles.size() + 1 << text["CreateNewSaveOption"] << "\n";
    std::cout << text["ChooseSaveSlot"];

    size_t choice;
    std::cin >> choice;

    if (choice >= 1 && choice <= saveFiles.size()) {
        path = saveFiles[choice - 1].string();
    }
    else {
        std::string newName;
        std::cout << text["EnterNewSaveName"];
        std::cin >> newName;

        path = saveDirectory + "/" + newName + ".json";

        try {
            fs::copy_file("json/Player.json", path);
            std::string msg = text["NewSaveCreated"];
            msg = std::regex_replace(msg, std::regex("\\{path\\}"), path);
            std::cout << msg << "\n";
        }
        catch (const fs::filesystem_error& e) {
            std::string msg = text["FailedToCreateSave"];
            msg = std::regex_replace(msg, std::regex("\\{error\\}"), e.what());
            std::cerr << msg << "\n";
        }
    }

    std::cout << "\033[2J\033[H";
}

void SaveManager::SaveGame(Creature& player) {
    json j;
    j["Name"] = player.GetName();
    j["Strength"] = std::to_string(player.GetStrength());
    j["Hp"] = std::to_string(player.GetHp());
    j["Armor"] = std::to_string(player.GetPermanentArmor());
    j["Money"] = std::to_string(player.GetMoney());

    const auto& inv = player.GetInventory().GetAllItems();
    j["Inventory"] = json::array();
    for (const auto& item : inv) {
        j["Inventory"].push_back(item.GetPath());
    }

    std::ofstream out(path);
    if (!out.is_open()) {
        std::cerr << text["FailedToOpenSave"] << "\n";
        return;
    }

    out << j.dump(4);

    std::string msg = text["GameSaved"];
    msg = std::regex_replace(msg, std::regex("\\{path\\}"), path);
    std::cout << msg << "\n";
}

std::string SaveManager::GetPath() const {
    return path;
}
