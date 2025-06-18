#pragma once
#include "Creature.h"
#include <iostream>
#include "json.hpp"
#include "Random.h"

class BattleManager
{

private:
	BattleManager() = default;
	~BattleManager() = default;

	BattleManager(const BattleManager&) = delete;
	BattleManager& operator=(const BattleManager&) = delete;

public:


	static BattleManager& getInstance();

	int StartRegularBattle(Creature& Enemy, Creature& Player);
};

