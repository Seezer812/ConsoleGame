#include "Market.h"
#include "json.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

using json = nlohmann::json;

Market::Market(const std::string& jsonPath) {
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open market JSON file: " + jsonPath);
    }

    json itemPathsJson;
    file >> itemPathsJson;

    if (!itemPathsJson.is_array()) {
        throw std::runtime_error("Invalid market JSON format: expected array of paths");
    }

    for (const auto& path : itemPathsJson) {
        if (!path.is_string()) continue;

        try {
            Item item(path.get<std::string>());
            stock.AddItem(item);
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to load item from: " << path << " (" << e.what() << ")" << std::endl;
        }
    }
    path = jsonPath;
}

void Market::DisplayItems() const {
    std::cout << "Items available in the market:\n";
    if (!stock.GetAllItems().empty()) {
        stock.ListItems();
    }
    else {
        std::cout << "You buy all items\n";
    }
}

InventoryManager& Market::GetStock() {
    return stock;
}


void Market::BuyItem(Creature& buyer) {


    while (true) {
        DisplayItems();
        std::cout << "- Exit\n";
        std::cout << "Your money: " << buyer.GetMoney() << std::endl;
        std::string i;
        std::cin >> i;
        if (i != "Exit") {
            if (stock.HasItem(i)) {
                if (stock.GetItem(i)->GetPrice() <= buyer.GetMoney()) {
                    system("cls");
                    std::cout << "You buy: " << i << "\n";
                    buyer.SpendMoney(stock.GetItem(i)->GetPrice());
                    buyer.AddItem(*stock.GetItem(i));
                    stock.RemoveItem(i);

                }
                else {
                    system("cls");
                    std::cout << "You don't have enough money\n";
                }
            }
            else {
                system("cls");
                std::cout << "You enter wrong item name\n";
            }
        }
        else {
            break;
        }
    }
}

