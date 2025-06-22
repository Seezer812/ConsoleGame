#include "Item.h"


Item::Item() : name("Unknown"), type("Unknown"), strength(0), price(0) {}


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


std::string Item::GetName() const
{
    return name;
}


std::string Item::GetType() const
{
    return type;
}

int Item::GetStrength() const
{
    return strength;
}




void Item::SetName(std::string new_name)
{
    name = new_name;
}

void Item::SetType(std::string new_type)
{
    type = new_type;
}

void Item::SetStrength(int new_strength)
{
    strength = new_strength;
}

void Item::SetPrice(int new_price)
{
    price = new_price;
}



int Item::GetPrice() const
{
    return price;
}

