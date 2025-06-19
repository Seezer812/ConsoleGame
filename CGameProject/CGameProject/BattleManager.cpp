#include "BattleManager.h"
BattleManager& BattleManager::getInstance() {
    static BattleManager instance;
    return instance;
}


int BattleManager::StartRegularBattle(Creature& player, Creature& enemy) {
    std::cout << enemy.GetDialogues().at("StartFight")[Random::randint(0, enemy.GetDialogues().at("StartFight").size()) - 1] << "\n";
    std::cout << "Press Enter to begin the fight...";
    std::cin.ignore();

    while (player.GetHp() > 0 and enemy.GetHp() > 0) {
        system("cls");

        enemy.TakeDamage(player.GetAttack());
        std::cout << player.GetDialogues().at("Attack")[Random::randint(0, player.GetDialogues().at("Attack").size()) - 1]
            << " Enemy HP: " << enemy.GetHp() << "\n";

        if (enemy.GetHp() <= 0) break;

        player.TakeDamage(enemy.GetAttack());
        std::cout << enemy.GetDialogues().at("Attack")[Random::randint(0, enemy.GetDialogues().at("Attack").size()) - 1]
            << " Player HP: " << player.GetHp() << "\n";

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
    }

    system("cls");

    if (player.GetHp() > 0) {
        std::cout << enemy.GetDialogues().at("Victory")[Random::randint(0, enemy.GetDialogues().at("Victory").size()) - 1] << "\n";
        return 1;
    }
    else {
        std::cout << enemy.GetDialogues().at("Defeat")[Random::randint(0, enemy.GetDialogues().at("Defeat").size()) - 1] << "\n";
        return 0;
    }
}

