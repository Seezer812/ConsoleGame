#include "Creature.h"

Creature::Creature(const std::string& json_filename) {
	std::ifstream file(json_filename);
	if (!file.is_open()) {
		std::cerr << ("Не удалось открыть файл JSON: " + json_filename);
	}

	json j;
	file >> j;

	if (j.contains("Name")) {
		name = j["Name"].get<std::string>();
	}

	if (j.contains("Strength")) {
		strength = std::stoi(j["Strength"].get<std::string>());
	}
	else {
		strength = 0;
	}

	if (j.contains("Hp")) {
		hp = std::stoi(j["Hp"].get<std::string>());
	}
	else {
		hp = 0;
	}

	if (j.contains("Armor")) {
		armor = std::stoi(j["Armor"].get<std::string>());
	}
	else {
		armor = 0;
	}

	if (j.contains("Money")) {
		money = std::stoi(j["Money"].get<std::string>());
	}
	else {
		money = 0;
	}

	if (j.contains("Dialogues")) {
		dialogues.clear();
		for (auto& [key, arr] : j["Dialogues"].items()) {
			if (arr.is_array()) {
				for (auto& phrase : arr) {
					dialogues[key].push_back(phrase.get<std::string>());
				}
			}
		}
	}

	temp_armor = 0;
	attack_boost = 0;
	attack_penalty = 0;
}

std::string Creature::GetName() const {
	return name;
}

int Creature::GetStrength() const {
	return strength;
}

int Creature::GetHp() const
{
	return hp;
}

int Creature::GetArmor() const
{
	return armor + temp_armor;
}

int Creature::GetPermanentArmor() const
{
	return armor;
}


int Creature::GetMoney() const
{
	return money;
}

std::unordered_map <std::string, std::vector<std::string>> Creature::GetDialogues() {
	return dialogues;
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

int Creature::GetAttack() {
	int total = strength + attack_boost - attack_penalty;
	attack_boost = 0;
	attack_penalty = 0;
	return total;
}


void Creature::TakeDamage(int amount) {
	int effectiveArmor = armor + temp_armor;
	int damage = amount - GetArmor();
	int reducedDamage = std::max(0, damage - effectiveArmor);
	hp -= reducedDamage;
	temp_armor = 0;
}

bool Creature::IsAlive() const {
	return hp > 0;
}

void Creature::SetTemporaryArmor(int value) {
	temp_armor = value;
}

void Creature::Heal(int amount) {
	hp += amount;
}

void Creature::BoostNextAttack(int amount) {
	attack_boost = amount;
}

void Creature::ReduceAttackTemporarily(int amount) {
	attack_penalty = amount;
}

