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
	Creature Player{ Save.GetPath() };

	std::string menuPath = "json/World1Info.json";

	Move Menu(menuPath, Player, Save);

	while (true) {

		Menu.StartChooseWay();

	}
}