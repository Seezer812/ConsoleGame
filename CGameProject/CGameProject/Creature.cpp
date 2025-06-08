#include "Creature.h"

int Creature::GetHp() const
{
    return hp;
}

int Creature::GetArmor() const
{
    return armor;
}

int Creature::GetMoney() const
{
    return money;
}

std::vector<std::shared_ptr<Item>>& Creature::GetInventory()
{
    return inventory;
}

void Creature::SetHp(int new_hp)
{
    hp = new_hp;
}

void Creature::SetArmor(int new_armor)
{
    armor = new_armor;
}

void Creature::SetMoney(int new_money)
{
    money = new_money;
}
