#include "Move.h"

#include <fstream>
#include <sstream>
#include <iostream>


Move::Move(std::string path, Creature& Player, Market& Market)
    : player(Player), market(Market)
{

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл JSON: " + path);
    }

    file >> move_text;

    if (move_text.contains("PathEnemy1")) {
        for (const auto& [key, path] : move_text.items()) {
            if (key.find("PathEnemy") != std::string::npos) {
                Creature obj(path.get<std::string>());
                enemies.push_back(obj);
            }
            else if (key.find("PathBoss") != std::string::npos) {
                Creature obj(path.get<std::string>());
                boss = obj;
            }
            else if (key.find("PathMarket") != std::string::npos) {
                return;
            }
        }
    }
}

std::string Move::GetMoveText(const std::string& key)
{
    if (move_text.contains(key)) return move_text[key];
    return "[Missing string: " + key + "]";
}

void Move::UseItem()
{
    while (true) {
        player.GetInventory().ListItems();
        std::cout << "- Exit\n";

        std::string i;
        std::cin >> i;

        if (i == "Exit")
            break;

        if (!player.GetInventory().HasItem(i)) {
            std::cout << "\033[2J\033[H";
            std::cout << "You entered an incorrect item name\n";
            continue;
        }

        Item* item = player.GetInventory().GetItem(i);
        if (!item) {
            std::cout << "Error: item not found.\n";
            continue;
        }

        std::string type = item->GetType();
        std::string name = item->GetName();

        std::cout << "\033[2J\033[H";

        if (type == "Weapon") {
            player.SetActiveWeapon(*item);
            std::cout << "You equipped weapon: " << name << "\n";
        }
        else if (type == "Armor") {
            player.SetActiveArmor(*item);
            std::cout << "You equipped armor: " << name << "\n";
        }
        else if (type == "Potion") {
            player.Heal(item->GetStrength());
            std::cout << "You used potion: " << name << "\n";
            player.RemoveItem(i);
        }
        else {
            std::cout << "Unknown item type.\n";
        }
    }
}

void Move::StartChooseWay()
{
    std::cout << GetMoveText("StartPromt");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int num_choice = 0;
    bool valid_input = false;

    while (!valid_input) {
        std::string choices = move_text["Choices"].get<std::string>();
        std::cout << choices << "\n";
        std::cout << GetMoveText("EnterText");

        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        if (ss >> num_choice && (num_choice >= 1 && num_choice <= 4)) {
            valid_input = true;
        }
        else {
            std::cout << GetMoveText("InvalidInput") << "\n";
            std::cin.ignore('\n');
            std::cout << "\033[2J\033[H";
        }

        switch (num_choice)
        {
        case 1:
            bm.StartRegularBattle(player, enemies[Random::Randint(0, enemies.size() - 1)]);
            break;
        case 2:
            bm.StartBossBattle(player, boss);
            break;
        case 3:
            market.BuyItem(player);
            break;
        case 4:
            UseItem();
            break;

        default:
            break;
        }
    }
}
