#include "Creature.h"
#include "BattleManager.h"
#include "Item.h"
#include "InventoryManager.h"
#include <iostream>

int main()
{
	InventoryManager inventory;
	Creature player{"json/Player.json"};

	player.GetInventory().ListItems();

}