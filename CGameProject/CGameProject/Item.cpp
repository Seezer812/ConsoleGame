#include "Item.h"


Item::Item(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open item file: " + path);
    }

    json j;
    file >> j;

    if (!j.contains("name") || !j.contains("type") ||
        !j.contains("strength") || !j.contains("price")) {
        throw std::runtime_error("Invalid item format in file: " + path);
    }

    name = j["name"].get<std::string>();
    type = j["type"].get<std::string>();
    strength = j["strength"].get<int>();
    price = j["price"].get<int>();
}

std::string Item::GetName()
{
    return name;
}

std::string Item::GetType()
{
    return type;
}

int Item::GetStrength()
{
    return strength;
}

int Item::GetPrice()
{
    return price;
}
