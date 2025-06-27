#include "Creature.h"
#include "BattleManager.h"
#include "Item.h"
#include "InventoryManager.h"
#include "SaveManager.h"
#include "Move.h"

#include <iostream>

int main()
{
	SaveManager Save;
	Creature Player{Save.GetPath()};
	Market Market{ "json/Market1.json" };
	Move Menu("json/World1Info.json", Player, Market, Save);

	while (true) {

		Menu.StartChooseWay();


	}

}