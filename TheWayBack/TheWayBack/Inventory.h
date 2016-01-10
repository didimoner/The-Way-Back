#pragma once
#include "Item.h"
#include "Window.h"
#include "TileMapLoader.h"
#include "ItemLoader.h"


class Inventory	:
	public ui::Window
{
public:
	Inventory(unsigned short size, float width, float height, std::string header, ItemLoader* itemLoader);
	~Inventory();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);
	virtual void setPosition(float x, float y);

	void load();
	void add(Item* item);
	bool contains(std::string name, int mode);

	int getSize();

private:
	std::vector<Item> _cells;
	unsigned short _size;
	ui::Window* _window;
	sf::Sprite* _grid;
	sf::Vector2f _gridOffset;
	ItemLoader* _pItemLoader;

};

