#pragma once
#include "Creature.h"
#include <string>
#include <unordered_map>
#include <conio.h>
#include <chrono>
#include <thread>
#include "json.hpp"

class BattleManager {
public:
    static BattleManager& getInstance();
    int StartRegularBattle(Creature& player, Creature& enemy);
    int StartBossBattle(Creature& player, Creature& boss);

private:
    BattleManager(); // приватный конструктор
    nlohmann::json battleText;
    std::string GetText(const std::string& key);
    std::string Format(const std::string& templateStr, const std::string& var, const std::string& value);
    void PrintTable(Creature player, Creature enemy);
};
