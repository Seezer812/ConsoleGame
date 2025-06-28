#include "InventoryManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

InventoryManager::InventoryManager() {
    std::ifstream file("json/InventoryManagerText.json");
    if (file.is_open()) {
        try {
            file >> texts;
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        }
    }
    else {
        std::cerr << "Failed to open inventory text JSON file: json/InventoryManagerText.json" <<  std::endl;
    }
}

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
        std::cout << texts.value("InventoryEmpty", "Inventory is empty.") << std::endl;
        return;
    }

    for (const auto& item : items) {
        std::string line = texts.value("InventoryItem", "- {Name} (Type: {Type}, Strength: {Strength}, Price: {Price})");

        size_t pos;
        pos = line.find("{Name}");
        line.replace(pos, 6, item.GetName());
        pos = line.find("{Type}");
        line.replace(pos, 6, item.GetType());
        pos = line.find("{Strength}");
        line.replace(pos, 10, std::to_string(item.GetStrength()));
        pos = line.find("{Price}");
        line.replace(pos, 7, std::to_string(item.GetPrice()));

        std::cout << line << std::endl;
    }
}

void InventoryManager::ListTypeItems(std::string type) const {
    if (items.empty()) {
        std::cout << texts.value("InventoryEmpty", "Inventory is empty.") << std::endl;
        return;
    }

    int i = 0;
    for (const auto& item : items) {
        if (item.GetType() == type) {
            i++;
            std::string line = texts.value("InventoryTypeItem", "{Index}. {Name} ({Strength})");

            size_t pos;
            pos = line.find("{Index}");
            if (pos != std::string::npos) line.replace(pos, 7, std::to_string(i));
            pos = line.find("{Name}");
            if (pos != std::string::npos) line.replace(pos, 6, item.GetName());
            pos = line.find("{Strength}");
            if (pos != std::string::npos) line.replace(pos, 10, std::to_string(item.GetStrength()));

            std::cout << line << std::endl;
        }
    }
}

const std::vector<Item>& InventoryManager::GetAllItems() const {
    return items;
}
