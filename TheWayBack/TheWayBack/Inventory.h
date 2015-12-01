#pragma once
#include "Item.h"
#include "Window.h"

class Inventory	:
	public ui::Window
{
public:
	Inventory(unsigned short size, float width, float height, std::string header);
	~Inventory();

	void load();
	void add(Item* item);
	bool contains(std::string name, int mode);

	int getSize();

private:
	std::vector<Item> _cells;
	unsigned short _size;
	ui::Window* _window;
};

