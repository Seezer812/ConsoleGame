#include "Creature.h"
#include "BattleManager.h"
#include "Item.h"
#include "InventoryManager.h"
#include "SaveManager.h"
#include "Move.h"

#include <iostream>

/*
TODO:
ƒобавить смену мира после победа над 1 боссом
¬есь вывод текста перенести в JSON
ƒобавить окно проигрыша при смерти
ƒобавить окно победы после победы над 2 боссом
*/ 

int main()
{
	SaveManager Save;
	Creature Player{ Save.GetPath() };

	std::string marketPath = "json/Market" + std::to_string(Player.GetWorldNum()) + ".json";
	std::string menuPath = "json/World" + std::to_string(Player.GetWorldNum()) + "Info.json";

	Market Market{ marketPath };
	Move Menu(menuPath, Player, Market, Save);

	while (true) {

		Menu.StartChooseWay();


	}

}