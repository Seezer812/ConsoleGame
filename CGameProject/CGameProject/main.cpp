#include "Creature.h"
#include "BattleManager.h"
#include "Item.h"
#include "InventoryManager.h"
#include "SaveManager.h"
#include "Move.h"

#include <iostream>

/*
TODO:
�������� ����� ���� ����� ������ ��� 1 ������
���� ����� ������ ��������� � JSON
�������� ���� ��������� ��� ������
�������� ���� ������ ����� ������ ��� 2 ������
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