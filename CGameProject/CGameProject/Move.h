#ifndef MOVE
#define MOVE

#include "json.hpp"
#include "Market.h"
#include "BattleManager.h";
#include "SaveManager.h"

#include <string>
#include <vector>

class Move
{
private:

	void ÑhangeWorld();

	std::string GetMoveText(const std::string& key);

	nlohmann::json move_text;
	std::vector<Creature> enemies;
	BattleManager& bm = BattleManager::GetInstance();
	Creature player;
	Creature boss;
	Market market;
	SaveManager save;
	std::string path;



public:

	Move(std::string path, Creature& Player, SaveManager& Save);

	void UseItem();
	void StartChooseWay();
};

#endif // !MOVE