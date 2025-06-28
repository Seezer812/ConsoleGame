#include "Market.h"
#include "json.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

Market::Market(const std::string& jsonPath) {
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open market JSON file: " + jsonPath);
    }
    
    file >> market_text;

    for (const auto& [key, path] : market_text.items()) {
        if (key.find("ItemPath") != std::string::npos) {
            Item item(path.get<std::string>());
            stock.AddItem(item);
        }
    }
}

std::string Market::GetMarketText(const std::string& key) const
{
    if (market_text.contains(key)) return market_text[key];
    return "[Missing string: " + key + "]";
}

void Market::DisplayItems() const {
    std::cout << GetMarketText("AvailableItems");
    if (!stock.GetAllItems().empty()) {
        stock.ListItems();
    }
    else {
        std::cout << GetMarketText("Reach");
    }
}

InventoryManager& Market::GetStock() {
    return stock;
}


void Market::BuyItem(Creature& buyer) {


    while (true) {
        DisplayItems();
        std::cout << GetMarketText("ExitText");
        std::cout << "Your money: " << buyer.GetMoney() << std::endl;
        std::string i;
        std::cin >> i;
        if (i != "Exit") {
            if (stock.HasItem(i)) {
                if (stock.GetItem(i)->GetPrice() <= buyer.GetMoney()) {
                    std::cout << "\033[2J\033[H";
                    std::cout << "You buy: " << i << "\n";
                    buyer.SpendMoney(stock.GetItem(i)->GetPrice());
                    buyer.AddItem(*stock.GetItem(i));
                    stock.RemoveItem(i);

                }
                else {
                    std::cout << "\033[2J\033[H";
                    std::cout << GetMarketText("Broke");
                }
            }
            else {
                std::cout << "\033[2J\033[H";
                std::cout << GetMarketText("WrongName");
            }
        }
        else {
            break;
        }
    }
}

