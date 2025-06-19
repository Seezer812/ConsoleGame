#ifndef CREATURE
#define CREATURE

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Item.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

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
	std::vector <std::shared_ptr<Item>> inventory;

public:
	Creature(const std::string& path);

	std::unordered_map <std::string, std::vector<std::string>> GetDialogues();
	std::vector<std::shared_ptr<Item>>& GetInventory();

	std::string GetName() const;
	int GetStrength() const;
	int GetHp() const;
	int GetArmor() const;
	int GetMoney() const;

	void SetHp(int new_hp);
	void SetArmor(int new_armor);
	void SetMoney(int new_money);

	int GetAttack();
	void TakeDamage(int amount);
	bool IsAlive() const;

	// New mechanics
	void SetTemporaryArmor(int value);
	void Heal(int amount);
	void BoostNextAttack(int amount);
	void ReduceAttackTemporarily(int amount);

	void ResetTurnModifiers();
};

#endif // !CREATURE