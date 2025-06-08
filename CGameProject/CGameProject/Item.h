#ifndef ITEM
#define ITEM

#include <string>

class Item
{
private:
	const std::wstring name;
	const int price;
public:
	const void GetName() const;
	void GetPrice() const;

	Item(const std::wstring& name, const int price);
};

#endif // !ITEM