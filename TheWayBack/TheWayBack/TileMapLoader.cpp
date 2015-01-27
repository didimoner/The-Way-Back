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

	// TILESET!
	// <tileset firstgid="257" name="tilea2" tilewidth="32" tileheight="32">
	// <image source="../../../../../../TheWayBack Files/ТайлСеты/tilea2.png" width="512" height="384"/>
	tinyxml2::XMLElement* pTileset = pRoot->FirstChildElement("tileset");
	tinyxml2::XMLElement* pImage;

	while (pTileset != nullptr)
	{
		pImage = pTileset->FirstChildElement("image");
		// Додумать это место...
		pTileset = pTileset->NextSiblingElement("tileset");
	}

	// получение layer and tile

	tinyxml2::XMLElement* pLayer = pRoot->FirstChildElement("layer");
	tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
	tinyxml2::XMLElement* pTile;

	std::vector<int> tempTiles;

	while (pLayer != nullptr)
	{
		pData = pLayer->FirstChildElement("data");
		pTile = pData->FirstChildElement("tile");

		while (pTile != nullptr)
		{
			tempTiles.push_back(pTile->IntAttribute("gid"));
			pTile = pTile->NextSiblingElement("tile");
		}

		_currentMap.push_back(tempTiles);

		pLayer = pLayer->NextSiblingElement("layer");
		tempTiles.clear();
	}

	// получение objectgroup

	tinyxml2::XMLElement* pObjectgroup = pRoot->FirstChildElement("objectgroup");
	std::string objectgroupName = "";

	tinyxml2::XMLElement* pObject;

	while (pObjectgroup != nullptr)
	{
		objectgroupName = pObjectgroup->Attribute("name");

		pObject = pObjectgroup->FirstChildElement("object");

		while (pObject != nullptr)
		{
			MapObject mapObject;
			mapObject.x = pObject->IntAttribute("x");
			mapObject.y = pObject->IntAttribute("y");
			mapObject.height = pObject->IntAttribute("height");
			mapObject.width = pObject->IntAttribute("width");

			_currentObjects[objectgroupName].push_back(mapObject);

			pObject = pObject->NextSiblingElement("object");
		}

		pObjectgroup = pObjectgroup->NextSiblingElement("objectgroup");
	}
}

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