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
    std::string path;
public:
    Market(const std::string& jsonPath);
    void DisplayItems() const;
    InventoryManager& GetStock();
    bool BuyItem(Creature& buyer);
};

#endif // MARKET_H