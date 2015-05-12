#include "Inventory.h"
#include <iostream>

Inventory::Inventory(unsigned short size)
{
	_size = size;
}


Inventory::~Inventory()
{
}

void Inventory::add(Item* item)
{
	if (_cells.size() <= _size)
	{
		_cells.push_back(*item);
		std::cout << "Item added: " << item->getName() << std::endl;
	}
	else
	{

	}
}

int Inventory::getSize()
{
	return _size;
}