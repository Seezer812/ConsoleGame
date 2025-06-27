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
	enum class MoveState
	{
		kEnemiesRoom,
		kBossRoom,
		kMarket,
		kBase
	};

	std::string GetMoveText(const std::string& key);
	nlohmann::json move_text;
	std::vector<Creature> enemies;
	BattleManager& bm = BattleManager::GetInstance();
	Creature player;
	Creature boss;
	Market market;
	SaveManager save;

public:

	Move(std::string path, Creature& Player, Market& Market, SaveManager& Save);

	void UseItem();
	void StartChooseWay();
};

#endif // !MOVE