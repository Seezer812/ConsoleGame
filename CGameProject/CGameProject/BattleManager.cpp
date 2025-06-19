#include "BattleManager.h"
BattleManager& BattleManager::getInstance() {
    static BattleManager instance;
    return instance;
}


int BattleManager::StartRegularBattle(Creature& player, Creature& enemy) {
    std::cout << enemy.GetDialogues().at("StartFight")[Random::randint(0, enemy.GetDialogues().at("StartFight").size())] << "\n";
    std::cout << "Press Enter to begin the fight...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (player.GetHp() > 0 && enemy.GetHp() > 0) {
        system("cls");

        std::cout << "Your HP: " << player.GetHp() << " | Enemy HP: " << enemy.GetHp() << "\n";
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
        bool skip_enemy_turn = false;

        switch (choice) {
        case 1: // Attack
            player_damage = player.GetAttack();
            std::cout << player.GetDialogues().at("Attack")[Random::randint(0, player.GetDialogues().at("Attack").size()-1)] << "\n";
            break;
        case 2: // Counter
            player_damage = player.GetAttack() / 2;
            player.SetTemporaryArmor(5);
            std::cout << "You counter!\n";
            break;
        case 3: // Heal
            player.Heal(15);
            std::cout << "You feel better.\n";
            break;
        case 4: // Power Hit
            if (Random::randint(0, 1) == 1) {
                player_damage = player.GetAttack() * 1.5;
                std::cout << "You unleash a mighty blow!\n";
            }
            else {
                std::cout << "Oh no! You miss\n";
            }
            break;
        case 5: // Taunt
            enemy.ReduceAttackTemporarily(5);
            std::cout << "You provoke your enemy.\n";
            break;
        case 6: // Focus
            player.BoostNextAttack(10);
            std::cout << "You steady your stance...\n";
            break;
        default:
            std::cout << "Invalid input. You lose your turn.\n";
            break;
        }

        enemy.TakeDamage(player_damage);
        std::cout << "Enemy HP: " << enemy.GetHp() << "\n";

        if (enemy.GetHp() <= 0) break;

        int damage = enemy.GetAttack();
        player.TakeDamage(damage);
        std::cout << enemy.GetDialogues().at("Attack")[Random::randint(0, enemy.GetDialogues().at("Attack").size()-1)] << "\n";
        std::cout << "You took " << damage << " damage. Your HP: " << player.GetHp() << "\n";

        std::cout << "\nPress Enter to continue...";
        std::cin.get();
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
