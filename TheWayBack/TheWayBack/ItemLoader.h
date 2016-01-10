#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"
#include "Constants.h"

#include "ContentManager.h"
#include "Entity.h"
#include "Item.h"
#include "SaveFileHandler.h"

struct ItemTileset
{
	std::string name;
	unsigned short width;
	unsigned short height;
};

struct Container
{
	Item container;
	std::vector<Item> items;
};

struct PreItem
{
	std::string id;
	std::string name;
	std::string desc;
	std::string need;
	bool state;
	unsigned short tileset;
	float width;
	float height;
	float left;
	float top;
	float offset_x;
	float offset_y;
	unsigned int tileId;
};

class ItemLoader
{
public:
	ItemLoader(std::string mapsDir, std::map<std::string, sf::Texture>* pTextures);
	~ItemLoader();

	void load(std::string name);

	std::vector<Item>* getItems();
	std::vector<Item>* getInventoryItems();
	std::vector<Container>* getContainers();

private:
	Item makeItem(PreItem* preItem, std::vector<ItemTileset>& tilesets);
	bool strToBool(std::string str);

	std::vector<ItemTileset> _itemTilesets;
	std::vector<PreItem> _itemsPre;
	std::vector<Item> _levelItems;
	std::vector<Item> _inventoryItems;
	std::vector<std::string> _inventoryItemsId;
	std::string _mapsDir;
	std::map <std::string, sf::Texture>* _pTextures;

	std::vector<Container> _containers;
};

