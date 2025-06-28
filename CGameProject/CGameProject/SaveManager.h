#ifndef SAVE
#define SAVE

#include <iostream>
#include "Creature.h"
#include "json.hpp"

class SaveManager
{
private:
    std::string path;
    nlohmann::json text;

public:
    SaveManager();
    void SaveGame(Creature& player);
    std::string GetPath() const;
};

#endif // !SAVE
