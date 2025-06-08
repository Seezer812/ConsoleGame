#ifndef CREATURE
#define CREATURE

#include <vector>
#include <memory>

#include "Item.h"

class Creature
{
private:
	std::vector<std::shared_ptr<Item>> inventory;
	int hp;
	int armor;
	int money;
public:
	std::vector<std::shared_ptr<Item>>& GetInventory();
	int GetHp() const;
	int GetArmor() const;
	int GetMoney() const;

	void SetHp(int new_hp);
	void SetArmor(int new_armor);
	void SetMoney(int new_money);
};

#endif // !CREATURE