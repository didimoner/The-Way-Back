#pragma once
#include "Item.h"

class Inventory
{
public:
	Inventory(unsigned short size);
	~Inventory();

	void update(float gameTime);
	void draw(sf::RenderWindow& window);

	void load();
	void add(Item* item);
	bool contains(std::string name);

	int getSize();

private:
	std::vector<Item> _cells;
	unsigned short _size;
};

