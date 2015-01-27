#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"

struct MapObject
{
	int x;
	int y;
	int width;
	int height;
};

class TileMapLoader
{
public:
	TileMapLoader();
	~TileMapLoader();

	void load(std::string name);
	void draw(sf::RenderWindow &window);

	void setMapsDir(std::string mapsDir);
	std::string getMapsDir();

private:
	std::string _mapsDir;
	std::vector<std::vector<int>> _currentMap;
	std::map<std::string, std::vector<MapObject>> _currentObjects;

	sf::Vector2i _tileSize;
	sf::Vector2i _mapSize;
};

