#include "TileMapLoader.h"

#include <iostream>
#include <fstream>

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

	if (tmxMap.ErrorID() != 0)
	{
		std::cout << "Error while opening " << path << " file!" << std::endl;
		return;
	}

	tinyxml2::XMLElement* pRoot = tmxMap.FirstChildElement("map");

	_mapSize.x = pRoot->IntAttribute("width");
	_mapSize.y = pRoot->IntAttribute("height");
	_tileSize.x = pRoot->IntAttribute("tilewidth");
	_tileSize.y = pRoot->IntAttribute("tileheight");

	tinyxml2::XMLElement* pLayer = pRoot->FirstChildElement("layer");
	tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
	tinyxml2::XMLElement* pTile;

	std::vector<int> tempTiles;

	while (pLayer != nullptr)
	{
		pData = pLayer->FirstChildElement("data");
		pTile = pData->FirstChildElement("tile");
		std::cout << "Layer name: " << pLayer->Attribute("name") << std::endl;

		while (pTile != nullptr)
		{
			int value;
			pTile->QueryIntAttribute("gid", &value);
			tempTiles.push_back(value);
			pTile = pTile->NextSiblingElement("tile");
		}

		//std::cout << "NumberOfTiles: " << b << std::endl;
		_currentMap.push_back(tempTiles);

		//std::cout << "current layer " << tempTiles[256] << std::endl;

		pLayer = pLayer->NextSiblingElement("layer");
		tempTiles.clear();
	}

	

	//std::cout << "NumberOfLayers: " << a << std::endl;

	std::cout << "Random numbers: " << _currentMap.size() << std::endl;
	std::cout << "Random numbers: " << _currentMap[0].size() << std::endl;
	std::cout << "Random numbers: " << _currentMap[1].size() << std::endl;

	std::ofstream fout;
	fout.open("Content/test.txt");

	for (int i = 0; i < _currentMap.size(); i++)
	{
		for (int j = 0; j < _currentMap[i].size(); j++)
		{
			fout << i << ":" << j << " " << _currentMap[i][j] << std::endl;
		}
	}

	fout.close();
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