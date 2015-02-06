#include "TileMapLoader.h"

#include <iostream>
#include <fstream>

TileMapLoader::TileMapLoader(std::string mapsDir, short entitiesLayer)
{
	_mapsDir = mapsDir + "/";
	_entitiesLayer = entitiesLayer;

}
TileMapLoader::~TileMapLoader()
{
}

void TileMapLoader::load(std::string name, std::map<std::string, sf::Texture>* pTextures)
{
	std::cout << "LET'S LOAD THIS SHIT!" << std::endl;
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

	// Load tilesets
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

	// load layers and tiles
	tinyxml2::XMLElement* pLayer = pRoot->FirstChildElement("layer");
	tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
	tinyxml2::XMLElement* pTile;

	std::vector<std::vector<sf::Sprite>> tempSpritesI;
	std::vector<sf::Sprite> tempSpritesJ;
	unsigned short tempGid;
	unsigned short tilesetIndex = 0;

	while (pLayer != nullptr)
	{
		pData = pLayer->FirstChildElement("data");
		pTile = pData->FirstChildElement("tile");

		for (int i = 0; i < _currentMap.height; i++)
		{
			for (int j = 0; j < _currentMap.width; j++)
			{
				tempGid = pTile->IntAttribute("gid");
				sf::Sprite tempSprite;

				if (tempGid == 0)
				{
					tempSprite.setColor(sf::Color::Transparent);
					tempSpritesJ.push_back(tempSprite);
					pTile = pTile->NextSiblingElement("tile");
					continue;
				}

				for (unsigned int l = 0; l < _currentTilesets.size(); l++)
				{
					if (_currentTilesets[l].firstgid >= tempGid)
						break;

					tilesetIndex = l;
				}

				tempSprite.setTexture((*_pTextures)[_currentTilesets[tilesetIndex].name]);

				short trueGid = tempGid - _currentTilesets[tilesetIndex].firstgid;

				short tilesetWidth = _currentTilesets[tilesetIndex].width / _currentTilesets[tilesetIndex].tileWidth;
				short tilesetHeight = _currentTilesets[tilesetIndex].height / _currentTilesets[tilesetIndex].tileHeight;

				short spritePositionX = (trueGid - tilesetWidth * (trueGid / tilesetWidth)) * _currentTilesets[tilesetIndex].tileWidth;
				short spritePositionY = (trueGid / tilesetWidth) * _currentTilesets[tilesetIndex].tileHeight;
				short spriteWidth = _currentTilesets[tilesetIndex].tileWidth;
				short spriteHeight = _currentTilesets[tilesetIndex].tileHeight;

				tempSprite.setTextureRect(sf::IntRect(spritePositionX, spritePositionY, spriteWidth, spriteHeight));

				short tileSizeW = _currentTilesets[tilesetIndex].tileWidth;
				short tileSizeH = _currentTilesets[tilesetIndex].tileHeight;

				tempSprite.setPosition(sf::Vector2f((float)j * tileSizeW, (float)i * tileSizeH));

				tempSpritesJ.push_back(tempSprite);
				pTile = pTile->NextSiblingElement("tile");
			}

			tempSpritesI.push_back(tempSpritesJ);
			tempSpritesJ.clear();

		}

		_currentMapSprites.push_back(tempSpritesI);
		tempSpritesI.clear();
		pLayer = pLayer->NextSiblingElement("layer");
	}

	// load objectgroups
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

void TileMapLoader::draw(sf::RenderWindow& window, std::vector<Entity*>& entities)
{
	for (unsigned int layer = 0; layer < _currentMapSprites.size(); layer++)
	{
		for (int tilesH = 0; tilesH < _currentMap.height; tilesH++)
		{
			for (int tilesW = 0; tilesW < _currentMap.width; tilesW++)
			{
				if (_currentMapSprites[layer][tilesH][tilesW].getColor() == sf::Color::Transparent)
					continue;

				window.draw(_currentMapSprites[layer][tilesH][tilesW]);
			}
		}

		if (_entitiesLayer == layer)
		{
			for (unsigned short i = 0; i < entities.size(); i++)
			{
				entities[i]->draw(window);
			}
		}
	}
}
