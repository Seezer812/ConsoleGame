#pragma once
#include "Creature.h"
#include <iostream>
#include "json.hpp"


class BattleManager
{

private:
	BattleManager() {}

public:
	BattleManager(const BattleManager&) = delete;
	BattleManager& operator=(const BattleManager&) = delete;

	static BattleManager& getInstance() {
		static BattleManager instance;
		return instance;
	}

	int NormalFight(Creature& Enemy, Creature& Player) {
		while (Enemy.GetHp() > 0 and Player.GetHp()) {

		}
	}
};

