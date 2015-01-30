#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"
#include "ContentManager.h"

struct Map
{
	unsigned short tileWidth;
	unsigned short tileHeight;
	unsigned short width;
	unsigned short height;
};

struct MapObject
{
	unsigned short x;
	unsigned short y;
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
	TileMapLoader(std::string mapsDir);
	~TileMapLoader();

	void load(std::string name, std::map<std::string, sf::Texture>* pTextures);
	void draw(sf::RenderWindow &window);

private:
	std::map <std::string, sf::Texture>* _pTextures;
	std::string _mapsDir;
	std::vector<std::vector<std::vector<unsigned short>>> _currentMapTiles;
	//std::vector<std::vector<std::vector<sf::Sprite>>> _currentMapSprites;
	std::map<std::string, std::vector<MapObject>> _currentObjects;
	std::vector<Tileset> _currentTilesets;
	Map _currentMap;
	
};

