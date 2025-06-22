#include "Creature.h"
#include "BattleManager.h"
#include "Item.h"
#include "InventoryManager.h"
#include <iostream>
#include "Move.h"

int main()
{
	Creature Player{"json/Player.json"};
	Market market{ "json/Market1.json" };
	Move menu("json/World1Info.json", Player, market);

	while (true) {

		menu.StartChooseWay();


	}

}