#include "InventoryManager.h"
#include <iostream>
#include <fstream>



void InventoryManager::AddItem(const Item& item) {
    items.push_back(item);
}

bool InventoryManager::RemoveItem(const std::string& name) {
    auto it = std::remove_if(items.begin(), items.end(),
        [&name](const Item& item) { return item.GetName() == name; });
    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

Item* InventoryManager::GetItem(const std::string& name) {
    for (auto& item : items) {
        if (item.GetName() == name)
            return &item;
    }
    return nullptr;
}

bool InventoryManager::HasItem(const std::string& name) const {
    for (const auto& item : items) {
        if (item.GetName() == name)
            return true;
    }
    return false;
}

void InventoryManager::ListItems() const {
    if (items.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    for (const auto& item : items) {
        std::cout << "- " << item.GetName() << " (Type: " << item.GetType()
            << ", Strength: " << item.GetStrength()
            << ", Price: " << item.GetPrice() << ")\n";
    }
}

void InventoryManager::ListTypeItems(std::string type) const {
    if (items.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    int i = 0;
    for (const auto& item : items) {
        if (item.GetType() == type) {
            i++;
            std::cout << i << ". " << item.GetName() << " ("
                << item.GetStrength() << ")\n";
        }
    }

}

void InventoryManager::SetActiveSword()
{
    ListTypeItems("Weapon");
    int i;
    int j = 0;
    std::cin >> i;
    for (const auto& item : items) {
        if (item.GetType() == "Weapon") {
            j++;
            if (i = j) {
                active_sword = item;
                break;
            }
        }
    }
}

void InventoryManager::SetActiveArmor()
{
    ListTypeItems("Armor");
    int i;
    int j = 0;
    std::cin >> i;
    for (const auto& item : items) {
        if (item.GetType() == "Armor") {
            j++;
            if (i = j) {
                active_armor = item;
                break;
            }
        }
    }
}

Item InventoryManager::GetActiveSword()
{
    return active_sword;
}

Item InventoryManager::GetActiveArmor()
{
    return active_armor;
}

const std::vector<Item>& InventoryManager::GetAllItems() const {
    return items;
}
