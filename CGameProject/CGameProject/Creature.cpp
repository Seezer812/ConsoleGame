#include "Creature.h"


Creature::Creature(const std::string& json_filename) {
    std::ifstream file(json_filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл JSON: " + json_filename);
    }

    json j;
    file >> j;

    if (j.contains("Name")) {
        name = j["Name"].get<std::string>();
    }

    if (j.contains("Strength")) {
        strength = std::stoi(j["Strength"].get<std::string>());
    }

    if (j.contains("Hp")) {
        hp = std::stoi(j["Hp"].get<std::string>());
    }
    else {
        hp = 0;
    }

    if (j.contains("Armor")) {
        armor = std::stoi(j["Armor"].get<std::string>());
    }
    else {
        armor = 0;
    }

    if (j.contains("Money")) {
        money = std::stoi(j["Money"].get<std::string>());
    }
    else {
        money = 0;
    }

    if (j.contains("Dialogues")) {
        dialogues.clear();
        for (auto& [key, arr] : j["Dialogues"].items()) {
            if (arr.is_array()) {
                for (auto& phrase : arr) {
                    dialogues[key].push_back(phrase.get<std::string>());
                }
            }
        }
    }
}

std::string Creature::GetName() const {
    return name;
}

int Creature::GetStrength() const {
    return strength;
}

int Creature::GetHp() const
{
    return hp;
}

int Creature::GetArmor() const
{
    return armor;
}

int Creature::GetMoney() const
{
    return money;
}

std::unordered_map <std::string, std::vector<std::string>> Creature::GetDialogues() {
    return dialogues;
}

std::vector<std::shared_ptr<Item>>& Creature::GetInventory()
{
    return inventory;
}

void Creature::SetHp(int new_hp)
{
    hp = new_hp;
}

void Creature::SetArmor(int new_armor)
{
    armor = new_armor;
}

void Creature::SetMoney(int new_money)
{
    money = new_money;
}
