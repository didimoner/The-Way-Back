#include "TileMapLoader.h"

#include <iostream>

TileMapLoader::TileMapLoader()
{
	_mapsDir = "";
}


TileMapLoader::~TileMapLoader()
{
}

void TileMapLoader::load(std::string name)
{
	std::string path = _mapsDir + name;
	const char* charPath = path.c_str();

	tinyxml2::XMLDocument tmxMap;
	tmxMap.LoadFile(charPath);
	std::cout << tmxMap.ErrorID() << std::endl;


	tinyxml2::XMLElement* pRoot = tmxMap.FirstChildElement("map");

	_mapSize.x = pRoot->IntAttribute("width");
	_mapSize.y = pRoot->IntAttribute("height");
	_tileSize.x = pRoot->IntAttribute("tilewidth");
	_tileSize.y = pRoot->IntAttribute("tileheight");

	tinyxml2::XMLElement* pLayer = pRoot->FirstChildElement("layer");
	tinyxml2::XMLElement* pTile = pLayer->FirstChildElement("data")->FirstChildElement("tile");


	int a = 0;
	int b = 0;

	while (pLayer != nullptr)
	{
		while (pTile != nullptr)
		{
			int value;
			pTile->QueryIntAttribute("gid", &value);

			pTile = pTile->NextSiblingElement("tile");
			b++;
		}

		std::cout << "NumberOfTiles: " << b << std::endl;

		pLayer = pLayer->NextSiblingElement("layer");
		a++;
	}

	std::cout << "NumberOfLayers: " << a << std::endl;
}

//TODO: заполнить вектора


void TileMapLoader::draw(sf::RenderWindow &window)
{

}

void TileMapLoader::setMapsDir(std::string mapsDir)
{
	_mapsDir = mapsDir + "/";
}
std::string TileMapLoader::getMapsDir()
{
	return _mapsDir;
}