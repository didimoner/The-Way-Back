#pragma once
#include "SFML\Graphics.hpp"
#include "tinyxml\tinyxml2.h"

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

	sf::Vector2i _tileSize;
	sf::Vector2i _mapSize;
};

