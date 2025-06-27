#include "BattleManager.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>
#include <limits>
#include <sstream>

const std::string kReset = "\033[0m";
const std::string kBlue = "\033[34m";
const std::string kGreen = "\033[32m";
const std::string kRed = "\033[31m";

BattleManager::BattleManager() {
    std::ifstream file("json/BattleManager.json");
    if (file.is_open()) {
        file >> battle_text;
    }
    else {
        std::cerr << "Could not open BattleText.json!\n";
    }
}

BattleManager& BattleManager::GetInstance() {
    static BattleManager instance;
    return instance;
}

void BattleManager::PrintTable(Creature player, Creature enemy) {
    std::cout << "+----------------+----------+----------------+----------+\n";
    std::cout << "|" << kBlue << " Your Stat      " << kReset << "| "
        << kGreen << "Value    " << kReset << "|"
        << kBlue << " Enemy Stat     " << kReset << "| "
        << kRed << "Value    " << kReset << "|\n";
    std::cout << "+----------------+----------+----------------+----------+\n";

    std::cout << "| " << kBlue << std::left << std::setw(15) << "HP" << kReset << "| "
        << kGreen << std::left << std::setw(8) << player.GetHp() << kReset << " | "
        << kBlue << std::left << std::setw(15) << "HP" << kReset << "| "
        << kRed << std::left << std::setw(8) << enemy.GetHp() << kReset << " |\n";

    std::cout << "| " << kBlue << std::left << std::setw(15) << "Armor" << kReset << "| "
        << kGreen << std::left << std::setw(8) << player.GetPermanentArmor() << kReset << " | "
        << kBlue << std::left << std::setw(15) << "Armor" << kReset << "| "
        << kRed << std::left << std::setw(8) << enemy.GetPermanentArmor() << kReset << " |\n";

    std::cout << "| " << kBlue << std::left << std::setw(15) << "Strength" << kReset << "| "
        << kGreen << std::left << std::setw(8) << player.GetStrength() << kReset << " | "
        << kBlue << std::left << std::setw(15) << "Strength" << kReset << "| "
        << kRed << std::left << std::setw(8) << enemy.GetStrength() << kReset << " |\n";

    std::cout << "+----------------+----------+----------------+----------+\n";
}

std::string BattleManager::GetText(const std::string& key) {
    if (battle_text.contains(key)) return battle_text[key];
    return "[Missing string: " + key + "]";
}

std::string BattleManager::Format(const std::string& templateStr, const std::string& var, const std::string& value) {
    std::string result = templateStr;
    std::regex pattern("\\{" + var + "\\}");
    return std::regex_replace(result, pattern, value);
}

int BattleManager::StartRegularBattle(Creature& player, Creature& enemy) {
    std::cout << enemy.GetDialogues().at("StartFight")[Random::Randint(0, enemy.GetDialogues().at("StartFight").size() - 1)] << "\n";
    std::cout << GetText("StartFightPrompt") << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (player.GetHp() > 0 && enemy.GetHp() > 0) {
        std::cout << "\033[2J\033[H";

        PrintTable(player, enemy);

        int choice = 0;
        bool valid_input = false;

        while (!valid_input) {
            std::cout << GetText("ChooseAction") << "\n";
            std::vector<std::string> actions = battle_text["Actions"].get<std::vector<std::string>>();
            for (const auto& action : actions)
                std::cout << action << "\n";

            std::cout << GetText("EnterText");

            std::string input;
            std::getline(std::cin, input);

            std::stringstream ss(input);
            if (ss >> choice && (choice >= 1 && choice <= 6)) {
                valid_input = true;
            }
            else {
                std::cout << GetText("InvalidInput") << "\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[2J\033[H";
                PrintTable(player, enemy);
            }
        }

        int player_damage = 0;

        std::cout << "\n" << GetText("YourTurn") << "\n";

        switch (choice) {
        case 1:
            player_damage = player.GetAttack();
            std::cout << Format(GetText("AttackDealt"), "value", std::to_string(player_damage)) << "\n";
            break;
        case 2:
            player_damage = player.GetAttack() / 2;
            player.SetTemporaryArmor(5);
            std::cout << Format(GetText("CounterDealt"), "value", std::to_string(player_damage)) << "\n";
            break;
        case 3:
            player.Heal(15);
            std::cout << GetText("HealUsed") << "\n";
            break;
        case 4:
            if (Random::Randint(0, 1) == 1) {
                player_damage = static_cast<int>(player.GetAttack() * 1.5);
                std::cout << Format(GetText("AttackDealt"), "value", std::to_string(player_damage)) << "\n";
            }
            else {
                std::cout << GetText("Missed") << "\n";
            }
            break;
        case 5:
            enemy.ReduceAttackTemporarily(5);
            std::cout << GetText("TauntUsed") << "\n";
            break;
        case 6:
            player.BoostNextAttack(10);
            std::cout << GetText("FocusUsed") << "\n";
            break;
        }

        enemy.TakeDamage(player_damage);

        if (enemy.GetHp() <= 0) break;

        int enemy_choice = Random::Randint(1, 6);
        int enemy_damage = 0;

        std::cout << "\n" << Format(GetText("EnemyTurn"), "enemy", enemy.GetName()) << "\n";

        switch (enemy_choice) {
        case 1:
            enemy_damage = enemy.GetAttack();
            std::cout << Format(GetText("EnemyAttack"), "enemy", enemy.GetName());
            std::cout << Format(GetText("EnemyDealt"), "value", std::to_string(enemy_damage)) << "\n";
            break;
        case 2:
            enemy_damage = enemy.GetAttack() / 2;
            enemy.SetTemporaryArmor(5);
            std::cout << Format(GetText("EnemyCounter"), "enemy", enemy.GetName());
            std::cout << Format(GetText("EnemyDealt"), "value", std::to_string(enemy_damage)) << "\n";
            break;
        case 3:
            enemy.Heal(15);
            std::cout << Format(GetText("EnemyHeal"), "enemy", enemy.GetName()) << "\n";
            break;
        case 4:
            if (Random::Randint(0, 1) == 1) {
                enemy_damage = static_cast<int>(enemy.GetAttack() * 1.5);
                std::cout << Format(GetText("EnemyPowerHit"), "enemy", enemy.GetName());
                std::cout << Format(GetText("EnemyDealt"), "value", std::to_string(enemy_damage)) << "\n";
            }
            else {
                std::cout << Format(GetText("EnemyMissed"), "enemy", enemy.GetName()) << "\n";
            }
            break;
        case 5:
            player.ReduceAttackTemporarily(5);
            std::cout << Format(GetText("EnemyTaunt"), "enemy", enemy.GetName()) << "\n";
            break;
        case 6:
            enemy.BoostNextAttack(10);
            std::cout << Format(GetText("EnemyFocus"), "enemy", enemy.GetName()) << "\n";
            break;
        }

        player.TakeDamage(enemy_damage);

        std::cout << "\n" << GetText("ContinuePrompt") << "\n";
        std::cin.get();
    }

    std::cout << "\033[2J\033[H";

    if (player.GetHp() > 0) {
        std::cout << enemy.GetDialogues().at("Victory")[Random::Randint(0, enemy.GetDialogues().at("Victory").size() - 1)] << "\n";
        player.SetMoney(player.GetMoney() + enemy.GetMoney());
        return 1;
    }
    else {
        std::cout << enemy.GetDialogues().at("Defeat")[Random::Randint(0, enemy.GetDialogues().at("Defeat").size() - 1)] << "\n";
        return 0;
    }
}


int BattleManager::StartBossBattle(Creature& player, Creature& boss) {
    std::cout << boss.GetDialogues().at("StartFight")[Random::Randint(0, boss.GetDialogues().at("StartFight").size() - 1)] << "\n";
    std::cout << GetText("StartBossBattlePrompt") << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const int timeLimitSeconds = 5;

    while (player.GetHp() > 0 && boss.GetHp() > 0) {
        const int comboLength = Random::Randint(3, 8);
        std::cout << "\033[2J\033[H";
        PrintTable(player, boss);

        std::string command;
        for (int i = 0; i < comboLength; ++i) {
            char c = 'A' + Random::Randint(0, 25);
            command += c;
        }

        std::cout << Format(GetText("BossComboPrompt"), "combo", command) << "\n";
        std::cout << Format(GetText("TimeLimitInfo"), "seconds", std::to_string(timeLimitSeconds)) << "\n";

        auto startTime = std::chrono::steady_clock::now();
        std::string input;
        std::getline(std::cin, input);
        auto endTime = std::chrono::steady_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
        for (auto& c : input) c = std::toupper(c);

        if (input == command && elapsed <= timeLimitSeconds) {
            std::cout << GetText("PlayerComboSuccess") << "\n";
            boss.TakeDamage(player.GetStrength());
        }
        else {
            std::cout << GetText("PlayerComboFail") << "\n";
        }

        if (boss.GetHp() <= 0) break;

        int boss_damage = boss.GetAttack();
        player.TakeDamage(boss_damage);

        std::cout << Format(GetText("BossAttacks"), "enemy", boss.GetName());
        std::cout << Format(GetText("EnemyDealt"), "value", std::to_string(boss_damage)) << "\n";

        std::cout << GetText("ContinuePrompt") << "\n";
        std::cin.get();
    }

    std::cout << "\033[2J\033[H";

    if (player.GetHp() > 0) {
        std::cout << boss.GetDialogues().at("Victory")[Random::Randint(0, boss.GetDialogues().at("Victory").size() - 1)] << "\n";
        player.UpWorld();
        return 1;
    }
    else {
        std::cout << boss.GetDialogues().at("Defeat")[Random::Randint(0, boss.GetDialogues().at("Defeat").size() - 1)] << "\n";
        return 0;
    }
}