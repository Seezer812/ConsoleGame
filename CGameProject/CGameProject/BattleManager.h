#pragma once
#include "Creature.h"
#include <string>
#include <unordered_map>
#include "json.hpp"

class BattleManager {
public:
    static BattleManager& getInstance();
    int StartRegularBattle(Creature& player, Creature& enemy);

private:
    BattleManager(); // приватный конструктор
    nlohmann::json battleText;
    std::string GetText(const std::string& key);
    std::string Format(const std::string& templateStr, const std::string& var, const std::string& value);
    void PrintTable(Creature player, Creature enemy);
};
