#ifndef SAVE
#define SAVE

#include <iostream>

#include "Creature.h"

class SaveManager
{
private:

	std::string path;

public:

	SaveManager();
	void SaveGame(Creature& player);
	std::string GetPath() const;
};

#endif // !SAVE
