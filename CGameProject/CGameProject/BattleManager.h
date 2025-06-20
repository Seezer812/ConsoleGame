#ifndef BATTLE
#define BATTLE

#include "json.hpp"
#include "Creature.h"

#include <string>
#include <unordered_map>



class BattleManager {
public:
    static BattleManager& GetInstance();
    int StartRegularBattle(Creature& player, Creature& enemy);

private:
    BattleManager(); // приватный конструктор
    nlohmann::json battle_text;
    std::string GetText(const std::string& key);
    std::string Format(const std::string& templateStr, const std::string& var, const std::string& value);
    void PrintTable(Creature player, Creature enemy);
};


#endif // !BATTLE