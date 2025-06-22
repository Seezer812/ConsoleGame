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

	Item();
	Item(std::string path);

	std::string GetName() const;
	std::string GetType() const;

	int GetStrength() const;
	int GetPrice() const;


	void SetName(std::string new_name);
	void SetType(std::string new_type);

	void SetStrength(int new_strength);
	void SetPrice(int new_price);

};

#endif // !ITEM