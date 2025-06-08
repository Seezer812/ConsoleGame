#include "Item.h"



const std::wstring& Item::GetName() const
{
    return name;
}

int Item::GetPrice() const
{
    return price;
}

Item::Item(const std::wstring& name, const int price) : name(name), price(price) {}