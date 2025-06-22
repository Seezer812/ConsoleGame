#ifndef CREATURE
#define CREATURE

#include "Item.h"
#include "json.hpp"
#include "InventoryManager.h"

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using json = nlohmann::json;

class Creature
{
private:
	std::string name;
	int hp;
	int armor;
	int money;
	int strength;

	int temp_armor = 0;
	int attack_boost = 0;
	int attack_penalty = 0;

	std::unordered_map <std::string, std::vector<std::string>> dialogues;
	InventoryManager inventory;

public:
	Creature(const std::string& path);

	std::unordered_map <std::string, std::vector<std::string>> GetDialogues();
	InventoryManager GetInventory();

	std::string GetName() const;
	int GetStrength() const;
	int GetHp() const;
	int GetArmor() const;
	int GetMoney() const;
	int GetPermanentArmor() const;

	void SetHp(int new_hp);
	void SetArmor(int new_armor);
	void SetMoney(int new_money);

	int GetAttack();
	void TakeDamage(int amount);
	bool IsAlive() const;

	void SpendMoney(int value);
	void SetTemporaryArmor(int value);
	void Heal(int amount);
	void BoostNextAttack(int amount);
	void ReduceAttackTemporarily(int amount);

};

#endif // !CREATURE
