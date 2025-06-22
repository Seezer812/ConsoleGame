#ifndef ITEM
#define ITEM

#include <string>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;

class Item
{
private:
	std::string name;
	std::string type;
	int strength;
	int price;
public:
	Item(std::string path);

	std::string GetName();
	std::string GetType();

	int GetStrength();
	int GetPrice();

};

#endif // !ITEM