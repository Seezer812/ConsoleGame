#include <iostream>
#include "Creature.h"
#include "BattleManager.h"
#include <windows.h>
#include <fcntl.h>
#include <io.h>

int main()
{

	Creature Enemy1("json/Enemy1.json");
	Creature Player("json/Player.json");
	BattleManager& bm = BattleManager::getInstance();
	int winner;
	winner = bm.StartRegularBattle(Player, Enemy1);

}