#include "TileMapLoader.h"

#include <iostream>
#include <fstream>

TileMapLoader::TileMapLoader(std::string mapsDir, short entitiesLayer, std::map<std::string, sf::Texture>* pTextures)
{
	_mapsDir = mapsDir + "/";
	_entitiesLayer = entitiesLayer;
	_pTextures = pTextures;
}

TileMapLoader::~TileMapLoader()
{
	_currentMapSprites.clear();
	_currentObjects.clear();
	_currentTilesets.clear();
	
}

void TileMapLoader::load(std::string name)
{
	_currentMapSprites.clear();
	_currentObjects.clear();
	_currentTilesets.clear();

	std::string path = _mapsDir + name + ".tmx";
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
	_currentMap.name = name;

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
	tinyxml2::XMLElement* pProperties;
	tinyxml2::XMLElement* pProperty;

	while (pObjectgroup != nullptr)
	{
		objectgroupName = pObjectgroup->Attribute("name");

		pObject = pObjectgroup->FirstChildElement("object");

		while (pObject != nullptr)
		{
			pProperties = pObject->FirstChildElement("properties");

			MapObject tempObject;

			sf::FloatRect tempRect = sf::FloatRect(pObject->FloatAttribute("x"), pObject->FloatAttribute("y"),
				pObject->FloatAttribute("width"), pObject->FloatAttribute("height"));
			tempObject.rect = tempRect;

			if (pObject->Attribute("name"))
			{
				tempObject.name = pObject->Attribute("name");
			}
			else
			{
				tempObject.name = "";
			}

			// Properties

			if (pProperties == nullptr)
			{
				tempObject.initPosition = sf::Vector2f(0, 0);
			}
			else
			{
				pProperty = pProperties->FirstChildElement("property");

				while (pProperty != nullptr)
				{
					std::string propertyName = pProperty->Attribute("name");

					if (propertyName == "def_x")
					{
						tempObject.initPosition.x = pProperty->FloatAttribute("value");
					}
					if (propertyName == "def_y")
					{
						tempObject.initPosition.y = pProperty->FloatAttribute("value");
					}

					pProperty = pProperty->NextSiblingElement("property");
				}
			}

			_currentObjects[objectgroupName].push_back(tempObject);

			pObject = pObject->NextSiblingElement("object");
		}

		pObjectgroup = pObjectgroup->NextSiblingElement("objectgroup");
	}
}

sf::Vector2i TileMapLoader::getSize()
{
	return sf::Vector2i(_currentMap.width * TILE_W, _currentMap.height * TILE_H);
}

std::vector<MapObject>* TileMapLoader::getObjects(std::string name)
{
	return &(_currentObjects[name]);
}

Map TileMapLoader::getCurrentMap()
{
	return _currentMap;
}

std::string TileMapLoader::getMapsDir()
{
	return _mapsDir;
}

std::vector<std::vector<std::vector<sf::Sprite>>>* TileMapLoader::getSprites()
{
	return &_currentMapSprites;
}