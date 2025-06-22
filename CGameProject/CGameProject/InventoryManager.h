#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Item.h"

#include <vector>
#include <string>

class InventoryManager {
private:
    std::vector<Item> items;
    Item active_sword;
    Item active_armor;
public:
    InventoryManager() = default;

    void AddItem(const Item& item);
    bool RemoveItem(const std::string& name);
    Item* GetItem(const std::string& name);
    bool HasItem(const std::string& name) const;
    void ListItems() const;
    void ListTypeItems(std::string type) const;


    const std::vector<Item>& GetAllItems() const;
};

#endif // INVENTORY_MANAGER_H