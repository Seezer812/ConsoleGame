#ifndef MARKET_H
#define MARKET_H

#include "Item.h"
#include "InventoryManager.h"
#include "Creature.h"

#include <vector>
#include <string>

class Market {
private:
    InventoryManager stock;
    nlohmann::json market_text;

    std::string GetMarketText(const std::string& key) const;
public:
    Market(const std::string& jsonPath);
    Market() = default;

    void DisplayItems() const;
    InventoryManager& GetStock();
    void BuyItem(Creature& buyer);
};

#endif // MARKET_H