#pragma once
#include "Item.h"

class Inventory
{
public:
	Inventory(unsigned short size);
	~Inventory();

	void add(Item* item);

	int getSize();

private:
	std::vector<Item> _cells;
	unsigned short _size;
};

