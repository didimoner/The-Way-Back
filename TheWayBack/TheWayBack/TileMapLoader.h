#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"

#include "ContentManager.h"
#include "Entity.h"
#include "Item.h"

struct Map
{
	std::string name;
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

struct ItemTileset
{
	std::string name;
	unsigned short width;
	unsigned short height;
};

struct MapObject
{
	std::string name;
	sf::FloatRect rect;
	sf::Vector2f initPosition;
};

struct Container
{
	Item container;
	std::vector<Item> items;
};

class TileMapLoader
{
public:
	TileMapLoader(std::string mapsDir, short entitiesLayer, std::map<std::string, sf::Texture>* pTextures);
	~TileMapLoader();

	void load(std::string name);
	void draw(sf::RenderWindow& window, std::vector<Entity*>& entities, sf::View& camera);

	sf::Vector2i getSize();
	std::vector<MapObject>* getObjects(std::string name);
	std::vector<Item>* getItems();
	Map getCurrentMap();
	std::string getMapsDir();

	void setItemBoolAttr(std::string name, bool attr);

private:
	std::map <std::string, sf::Texture>* _pTextures;
	std::string _mapsDir;
	std::vector<std::vector<std::vector<sf::Sprite>>> _currentMapSprites;
	std::map< std::string, std::vector<MapObject> > _currentObjects;
	std::vector<Tileset> _currentTilesets;
	std::vector<Item> _mapItems;
	std::vector<Container> _containers;
	Map _currentMap;
	short _entitiesLayer;
	bool _isChanged;

	Item makeItem(tinyxml2::XMLElement* pMapObject, std::vector<ItemTileset>& tilesets);
};

