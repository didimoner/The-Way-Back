#include "TileMapLoader.h"

#include <iostream>
#include <fstream>

TileMapLoader::TileMapLoader(std::string mapsDir)
{
	_mapsDir = mapsDir + "/";
}
TileMapLoader::~TileMapLoader()
{
}

void TileMapLoader::load(std::string name, std::map<std::string, sf::Texture>* pTextures)
{
	_pTextures = pTextures;

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

	_currentMap.width = pRoot->IntAttribute("width");
	_currentMap.height = pRoot->IntAttribute("height");
	_currentMap.tileWidth = pRoot->IntAttribute("tilewidth");
	_currentMap.tileHeight = pRoot->IntAttribute("tileheight");

	// TILESET!
	tinyxml2::XMLElement* pTileset = pRoot->FirstChildElement("tileset");
	tinyxml2::XMLElement* pImage;

	Tileset tempTileset;

	while (pTileset != nullptr)
	{
		pImage = pTileset->FirstChildElement("image");
		
		tempTileset.firstgid = pTileset->IntAttribute("firstgid");
		tempTileset.name = pTileset->Attribute("name");
		tempTileset.tileWidth = pTileset->IntAttribute("tilewidth");
		tempTileset.tileHeight = pTileset->IntAttribute("tileheight");
		tempTileset.width = pImage->IntAttribute("width");
		tempTileset.height = pImage->IntAttribute("height");

		_currentTilesets.push_back(tempTileset);
		pTileset = pTileset->NextSiblingElement("tileset");
	}

	// получение layer and tile

	tinyxml2::XMLElement* pLayer = pRoot->FirstChildElement("layer");
	tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
	tinyxml2::XMLElement* pTile;

	std::vector<std::vector<unsigned short>> tempTilesI;
	std::vector<unsigned short> tempTilesJ;
	
	while (pLayer != nullptr)
	{
		pData = pLayer->FirstChildElement("data");
		pTile = pData->FirstChildElement("tile");

		for (int i = 0; i < _currentMap.width; i++)
		{
			for (int j = 0; j < _currentMap.height; j++)
			{
				tempTilesJ.push_back(pTile->IntAttribute("gid"));
				pTile = pTile->NextSiblingElement("tile");
			}

			tempTilesI.push_back(tempTilesJ);
			tempTilesJ.clear();

		}

		_currentMapTiles.push_back(tempTilesI);
		tempTilesI.clear();

		pLayer = pLayer->NextSiblingElement("layer");
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
	sf::Sprite tempSprite;

	for (unsigned int k = 0; k < _currentMapTiles.size(); k++)
	{
		for (int i = 0; i < _currentMap.width; i++)
		{
			for (int j = 0; j < _currentMap.height; j++)
			{
				if (_currentMapTiles[k][i][j] == 0)
					continue;

				int tilesetIndex = 0;

				for (unsigned int l = 0; l < _currentTilesets.size(); l++)
				{
					if (_currentTilesets[l].firstgid >= _currentMapTiles[k][i][j])
						break;

					tilesetIndex = l;
				}

				tempSprite.setTexture((*_pTextures)[_currentTilesets[tilesetIndex].name]);

				short tempGid = _currentMapTiles[k][i][j] - _currentTilesets[tilesetIndex].firstgid;

				short tilesetWidth = _currentTilesets[tilesetIndex].width / _currentTilesets[tilesetIndex].tileWidth;
				short tilesetHeight = _currentTilesets[tilesetIndex].height / _currentTilesets[tilesetIndex].tileHeight;

				short spritePositionX = (tempGid - tilesetWidth * ((tempGid - 1) / tilesetWidth)) * _currentTilesets[tilesetIndex].tileWidth;
				short spritePositionY = (tempGid / tilesetWidth) * _currentTilesets[tilesetIndex].tileHeight;
				short spriteWidth = _currentTilesets[tilesetIndex].tileWidth;
				short spriteHeight = _currentTilesets[tilesetIndex].tileHeight;

				tempSprite.setTextureRect(sf::IntRect(spritePositionX, spritePositionY, spriteWidth, spriteHeight));

				short tileSizeW = _currentTilesets[tilesetIndex].tileWidth;
				short tileSizeH = _currentTilesets[tilesetIndex].tileHeight;

				tempSprite.setPosition(sf::Vector2f((float)j * tileSizeW, (float)i * tileSizeH));

				window.draw(tempSprite);
			}
		}
	}
}