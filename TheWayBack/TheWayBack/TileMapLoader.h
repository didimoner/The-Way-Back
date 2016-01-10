#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"
#include "Constants.h"

#include "ContentManager.h"
#include "Entity.h"

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

struct MapObject
{
	std::string name;
	sf::FloatRect rect;
	sf::Vector2f initPosition;
};

class TileMapLoader
{
public:
	TileMapLoader(std::string mapsDir, short entitiesLayer, std::map<std::string, sf::Texture>* pTextures);
	~TileMapLoader();

	void load(std::string name);

	sf::Vector2i getSize();
	std::vector<MapObject>* getObjects(std::string name);
	Map getCurrentMap();
	std::string getMapsDir();
	std::vector<std::vector<std::vector<sf::Sprite>>>* getSprites();

private:
	std::map <std::string, sf::Texture>* _pTextures;
	std::string _mapsDir;
	std::vector<std::vector<std::vector<sf::Sprite>>> _currentMapSprites;
	std::map< std::string, std::vector<MapObject> > _currentObjects;
	std::vector<Tileset> _currentTilesets;
	
	Map _currentMap;
	short _entitiesLayer;
};

