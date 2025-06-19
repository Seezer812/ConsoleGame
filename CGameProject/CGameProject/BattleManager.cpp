#include "BattleManager.h"

const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";


BattleManager& BattleManager::getInstance() {
    static BattleManager instance;
    return instance;
}

int BattleManager::StartRegularBattle(Creature& player, Creature& enemy) {
    std::cout << enemy.GetDialogues().at("StartFight")[Random::randint(0, enemy.GetDialogues().at("StartFight").size() - 1)] << "\n";
    std::cout << "Press Enter to begin the fight...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    while (player.GetHp() > 0 && enemy.GetHp() > 0) {
        system("cls");

        std::cout << "+----------------+----------+----------------+----------+\n";
        std::cout << "|" << BLUE << " Your Stat      " << RESET << "| "
            << GREEN << "Value    " << RESET << "|"
            << BLUE << " Enemy Stat     " << RESET << "| "
            << RED << "Value    " << RESET << "|\n";
        std::cout << "+----------------+----------+----------------+----------+\n";

        std::cout << "| " << BLUE << std::left << std::setw(15) << "HP" << RESET << "| "
            << GREEN << std::left << std::setw(8) << player.GetHp() << RESET << " | "
            << BLUE << std::left << std::setw(15) << "HP" << RESET << "| "
            << RED << std::left << std::setw(8) << enemy.GetHp() << RESET << " |\n";

        std::cout << "| " << BLUE << std::left << std::setw(15) << "Armor" << RESET << "| "
            << GREEN << std::left << std::setw(8) << player.GetArmor() << RESET << " | "
            << BLUE << std::left << std::setw(15) << "Armor" << RESET << "| "
            << RED << std::left << std::setw(8) << enemy.GetArmor() << RESET << " |\n";

        std::cout << "| " << BLUE << std::left << std::setw(15) << "Strength" << RESET << "| "
            << GREEN << std::left << std::setw(8) << player.GetStrength() << RESET << " | "
            << BLUE << std::left << std::setw(15) << "Strength" << RESET << "| "
            << RED << std::left << std::setw(8) << enemy.GetStrength() << RESET << " |\n";

        std::cout << "+----------------+----------+----------------+----------+\n";



        std::cout << "Choose your action:\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Counter (block & reflect)\n";
        std::cout << "3. Heal\n";
        std::cout << "4. Power Hit\n";
        std::cout << "5. Taunt\n";
        std::cout << "6. Focus (stronger next hit)\n";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int player_damage = 0;

        std::cout << "\nYour turn:\n";

        switch (choice) {
        case 1:
            player_damage = player.GetAttack();
            std::cout << "You dealt: " << player_damage << " damage\n";
            break;
        case 2:
            player_damage = player.GetAttack() / 2;
            player.SetTemporaryArmor(5);
            std::cout << "You counter!\n";
            std::cout << "You dealt: " << player_damage << " damage\n";
            break;
        case 3:
            player.Heal(15);
            std::cout << "You feel better.\n";
            break;
        case 4:
            if (Random::randint(0, 1) == 1) {
                player_damage = static_cast<int>(player.GetAttack() * 1.5);
                std::cout << "You dealt: " << player_damage << " damage\n";
            }
            else {
                std::cout << "Oh no! You miss\n";
            }
            break;
        case 5:
            enemy.ReduceAttackTemporarily(5);
            std::cout << "You provoke your enemy.\n";
            break;
        case 6:
            player.BoostNextAttack(10);
            std::cout << "You steady your stance...\n";
            break;
        default:
            std::cout << "Invalid input. You lose your turn.\n";
            break;
        }

        enemy.TakeDamage(player_damage);

        if (enemy.GetHp() <= 0) break;

        int enemy_choice = Random::randint(1, 6);
        int enemy_damage = 0;

        std::cout << "\n" << enemy.GetName() << " turn:\n";

        switch (enemy_choice) {
        case 1:
            enemy_damage = enemy.GetAttack();
            std::cout << enemy.GetName() << " dealt: " << enemy_damage << " damage\n";
            break;
        case 2:
            enemy_damage = enemy.GetAttack() / 2;
            enemy.SetTemporaryArmor(5);
            std::cout << enemy.GetName() << " uses Counter!\n";
            std::cout << enemy.GetName() << " dealt: " << enemy_damage << " damage\n";
            break;
        case 3:
            enemy.Heal(15);
            std::cout << enemy.GetName() << " heals.\n";
            break;
        case 4:
            if (Random::randint(0, 1) == 1) {
                enemy_damage = static_cast<int>(enemy.GetAttack() * 1.5);
                std::cout << enemy.GetName() << " unleashes a mighty blow!\n";
                std::cout << enemy.GetName() << " dealt: " << enemy_damage << " damage\n";
            }
            else {
                std::cout << enemy.GetName() << " misses!\n";
            }
            break;
        case 5:
            player.ReduceAttackTemporarily(5);
            std::cout << enemy.GetName() << " provokes you.\n";
            break;
        case 6:
            enemy.BoostNextAttack(10);
            std::cout << enemy.GetName() << " focuses...\n";
            break;
        }

        player.TakeDamage(enemy_damage);

        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    system("cls");

    if (player.GetHp() > 0) {
        std::cout << enemy.GetDialogues().at("Victory")[Random::randint(0, enemy.GetDialogues().at("Victory").size() - 1)] << "\n";
        return 1;
    }
    else {
        std::cout << enemy.GetDialogues().at("Defeat")[Random::randint(0, enemy.GetDialogues().at("Defeat").size() - 1)] << "\n";
        return 0;
    }
}

