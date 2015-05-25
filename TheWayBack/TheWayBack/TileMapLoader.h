#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"

#include "ContentManager.h"
#include "Entity.h"
#include "Item.h"

struct Map
{
	unsigned short tileWidth;
	unsigned short tileHeight;
	unsigned short width;
	unsigned short height;
};

struct Tileset
{
	std::string name;
	unsigned short firstgid;
	unsigned short tileWidth;
	unsigned short tileHeight;
	unsigned short width;
	unsigned short height;
};


class TileMapLoader
{
public:
	TileMapLoader(std::string mapsDir, short entitiesLayer, std::map<std::string, sf::Texture>* pTextures);
	~TileMapLoader();

	void load(std::string name);
	void draw(sf::RenderWindow& window, std::vector<Entity*>& entities, sf::View& camera);

	sf::Vector2i getSize();
	std::vector<sf::FloatRect>* getObjects(std::string name);
	std::vector<Item>* getItems();

private:
	std::map <std::string, sf::Texture>* _pTextures;
	std::string _mapsDir;
	std::vector<std::vector<std::vector<sf::Sprite>>> _currentMapSprites;
	std::map<std::string, std::vector<sf::FloatRect>> _currentObjects;
	std::vector<Tileset> _currentTilesets;
	std::vector<Item> _mapItems;
	Map _currentMap;
	short _entitiesLayer;
	bool _isChanged;
};

