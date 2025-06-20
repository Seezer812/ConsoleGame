#include "Creature.h"
#include "BattleManager.h"

#include <iostream>

int main()
{
	Creature Enemy1("json/Enemy1.json");
	Creature Player("json/Player.json");
	BattleManager& bm = BattleManager::GetInstance();
	int winner;
	winner = bm.StartRegularBattle(Player, Enemy1);
}