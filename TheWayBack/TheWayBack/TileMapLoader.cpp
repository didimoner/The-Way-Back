#include "TileMapLoader.h"

#include <iostream>
#include <fstream>

TileMapLoader::TileMapLoader(std::string mapsDir, short entitiesLayer, std::map<std::string, sf::Texture>* pTextures)
{
	_mapsDir = mapsDir + "/";
	_entitiesLayer = entitiesLayer;
	_pTextures = pTextures;
	_isChanged = false;
}
TileMapLoader::~TileMapLoader()
{
	_currentMapSprites.clear();
	_currentObjects.clear();
	_currentTilesets.clear();
	_mapItems.clear();
}

void TileMapLoader::load(std::string name)
{
	_currentMapSprites.clear();
	_currentObjects.clear();
	_currentTilesets.clear();
	_mapItems.clear();

	_isChanged = true;

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

	//objects on the map

	path = _mapsDir + name + ".two";
	charPath = path.c_str();

	tinyxml2::XMLDocument objects;
	objects.LoadFile(charPath);

	if (objects.ErrorID() != 0)
	{
		std::cout << "Error while opening " << path << " file!" << std::endl;
		return;
	}

	tinyxml2::XMLElement* pMapObject = objects.FirstChildElement("object");
	tinyxml2::XMLElement* pItemTileset = objects.FirstChildElement("tileset");

	std::vector<ItemTileset> tilesets;

	while (pItemTileset != nullptr)
	{
		ItemTileset tempTilesetItem;
		tempTilesetItem.name = pItemTileset->Attribute("name");
		tempTilesetItem.width = pItemTileset->IntAttribute("width");
		tempTilesetItem.height = pItemTileset->IntAttribute("height");

		tilesets.push_back(tempTilesetItem);

		pItemTileset = pItemTileset->NextSiblingElement("tileset");
	}

	while (pMapObject != nullptr)
	{
		if (pMapObject->BoolAttribute("type"))
		{
			Container tempContainer;
			std::vector<Item> tempContainerItems;

			Item containerItem = makeItem(pMapObject, tilesets);

			tinyxml2::XMLElement* pItem = pMapObject->FirstChildElement("item");

			while (pItem != nullptr)
			{
				Item tempContainerItem = makeItem(pItem, tilesets);
				tempContainerItems.push_back(tempContainerItem);

				pItem = pItem->NextSiblingElement("item");
			}

			tempContainer.container = containerItem;
			tempContainer.items = tempContainerItems;

			_containers.push_back(tempContainer);
		}
		else
		{
			Item mapItem = makeItem(pMapObject, tilesets);
			_mapItems.push_back(mapItem);
		}

		pMapObject = pMapObject->NextSiblingElement("object");
	}
	
}

void TileMapLoader::draw(sf::RenderWindow& window, std::vector<Entity*>& entities, sf::View& camera)
{
	sf::Vector2f cameraSizeT = sf::Vector2f(std::ceil(camera.getSize().x / _currentMap.tileHeight),
		std::ceil(camera.getSize().y / _currentMap.tileWidth));

	sf::Vector2f leftTop = sf::Vector2f(std::floor((camera.getCenter().x - camera.getSize().x / 2) / _currentMap.tileHeight),
		std::floor((camera.getCenter().y - camera.getSize().y / 2) / _currentMap.tileWidth));
	sf::Vector2f bottomRight = sf::Vector2f(std::ceil((camera.getCenter().x + camera.getSize().x / 2) / _currentMap.tileHeight),
		std::ceil((camera.getCenter().y + camera.getSize().y / 2) / _currentMap.tileWidth));

	for (unsigned int layer = 0; layer < _currentMapSprites.size(); layer++)
	{
		for (int tilesH = (int)leftTop.y; tilesH < (int)bottomRight.y; tilesH++)
		{
			if (tilesH < 0 || tilesH >= _currentMap.height)
			{
				continue;
			}

			for (int tilesW = (int)leftTop.x; tilesW < (int)bottomRight.x; tilesW++)
			{
				if (tilesW < 0 || tilesW >= _currentMap.width)
				{
					continue;
				}

				if (_currentMapSprites[layer][tilesH][tilesW].getColor() == sf::Color::Transparent)
					continue;

				window.draw(_currentMapSprites[layer][tilesH][tilesW]);
			}
		}

		if (_entitiesLayer == layer)
		{
			for (unsigned short i = 0; i < _mapItems.size(); i++)
			{
				_mapItems[i].draw(window);
			}

			for (unsigned short i = 0; i < _containers.size(); i++)
			{
				_containers[i].container.draw(window);
			}

			if (_isChanged)
			{
				_isChanged = false;
			}

			for (unsigned short i = 0; i < entities.size(); i++)
			{
				entities[i]->draw(window);
			}
		}
	}
}

sf::Vector2i TileMapLoader::getSize()
{
	return sf::Vector2i(_currentMap.width * _currentMap.tileWidth, _currentMap.height * _currentMap.tileHeight);
}

std::vector<MapObject>* TileMapLoader::getObjects(std::string name)
{
	return &(_currentObjects[name]);
}

std::vector<Item>* TileMapLoader::getItems()
{
	return &_mapItems;
}

std::vector<Container>* TileMapLoader::getContainers()
{
	return &_containers;
}

Map TileMapLoader::getCurrentMap()
{
	return _currentMap;
}

std::string TileMapLoader::getMapsDir()
{
	return _mapsDir;
}

Item TileMapLoader::makeItem(tinyxml2::XMLElement* pMapObject, std::vector<ItemTileset>& tilesets)
{
	sf::Sprite sprite;

	unsigned short objectWidth = pMapObject->IntAttribute("width");
	unsigned short objectHeight = pMapObject->IntAttribute("height");
	unsigned int tileId = pMapObject->IntAttribute("tileid");
	unsigned int left = pMapObject->IntAttribute("left") ? pMapObject->IntAttribute("left") : 0;
	unsigned int top = pMapObject->IntAttribute("top") ? pMapObject->IntAttribute("top") : 0;
	unsigned short tilesetId = pMapObject->IntAttribute("tileset");

	unsigned int offset_x = pMapObject->IntAttribute("offset_x") ? pMapObject->IntAttribute("offset_x") : 0;
	unsigned int offset_y = pMapObject->IntAttribute("offset_y") ? pMapObject->IntAttribute("offset_y") : 0;

	unsigned int tilesetWidth = tilesets[tilesetId].width / objectWidth;
	unsigned int tilesetHeight = tilesets[tilesetId].height / objectHeight;

	short spritePositionX = (tileId - tilesetWidth * (tileId / tilesetWidth)) * objectWidth;
	short spritePositionY = (tileId / tilesetWidth) * objectHeight;

	sprite.setTexture((*_pTextures)[tilesets[tilesetId].name]);
	sprite.setTextureRect(sf::IntRect(spritePositionX, spritePositionY, objectWidth, objectHeight));
	sprite.setPosition(sf::Vector2f((float)left * _currentMap.tileWidth, (float)top * _currentMap.tileHeight));
	sprite.move(sf::Vector2f((float)offset_x, (float)offset_y));

	std::string description = pMapObject->GetText() ? pMapObject->GetText() : "";
	char* id = pMapObject->Attribute("id") ? pMapObject->Attribute("id") : "";
	bool itemState = pMapObject->BoolAttribute("state") ? pMapObject->BoolAttribute("state") : false;

	SaveFileHandler saveFile("Content/Saves/save.tws");
	saveFile.load();

	std::string response = saveFile.getElement("mapItems", id, "state");

	if (response != "NO_ATTR" || response != "NO_ITEM")
	{
		if (response == "hidden")
			itemState = false;
	}

	Item item(sprite, pMapObject->Attribute("name"), id, description);
	item.setState(itemState);

	return item;
}


bool TileMapLoader::strToBool(std::string str)
{
	if (str == "1" || str == "true" || str == "TRUE")
	{
		return true;
	}

	return false;
}