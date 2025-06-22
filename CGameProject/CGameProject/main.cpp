#include "Move.h"
#include "Creature.h"

#include <iostream>

int main()
{
	std::string way = "json/World1Info.json";
	Creature player("json/Player.json");
	Move mv(way, player);
	mv.StartChooseWay();
}