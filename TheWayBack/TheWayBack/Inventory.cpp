#include "Inventory.h"
#include <iostream>

Inventory::Inventory(unsigned short size, float width, float height, std::string header) :
	ui::Window(width, height, header)
{
	_size = size;
}


Inventory::~Inventory()
{
	delete _window;
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

bool Inventory::contains(std::string seed, int mode)
{
	for (unsigned int i = 0; i < _cells.size(); i++)
	{
		switch (mode)
		{
		case 0:
			if (_cells[i].getName() == seed) return true;
		case 1: 
			if (_cells[i].getId() == seed) return true;
		default:
			break;
		}
	}

	return false;
}