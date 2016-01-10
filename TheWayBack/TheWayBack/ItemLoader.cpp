#include "ItemLoader.h"


ItemLoader::ItemLoader(std::string mapsDir, std::map<std::string, sf::Texture>* pTextures)
{
	_mapsDir = mapsDir + "/";
	_pTextures = pTextures;

	// Загружаю предметы
	std::string path = "Content/Resources/items.twi";
	const char* charPath = path.c_str();

	tinyxml2::XMLDocument items;
	items.LoadFile(charPath);

	if (items.ErrorID() != 0)
	{
		std::cout << "Error while opening " << path << " file!" << std::endl;
	}
	else
	{
		tinyxml2::XMLElement* pItem = items.FirstChildElement("item");
		tinyxml2::XMLElement* pItemTileset = items.FirstChildElement("tileset");

		// формирую массив тайлсетов
		while (pItemTileset != nullptr)
		{
			ItemTileset tempTilesetItem;
			tempTilesetItem.name = pItemTileset->Attribute("name");
			tempTilesetItem.width = pItemTileset->IntAttribute("width");
			tempTilesetItem.height = pItemTileset->IntAttribute("height");

			_itemTilesets.push_back(tempTilesetItem);

			pItemTileset = pItemTileset->NextSiblingElement("tileset");
		}

		// формирую массив предметов
		while (pItem != nullptr)
		{
			PreItem preItem;

			preItem.name = pItem->Attribute("name");
			preItem.desc = (std::string)pItem->GetText();
			preItem.id = pItem->Attribute("id");
			preItem.tileId = pItem->IntAttribute("tileid");
			preItem.tileset = pItem->IntAttribute("tileset");
			preItem.width = pItem->FloatAttribute("width");
			preItem.height = pItem->FloatAttribute("height");

			preItem.need = "";
			preItem.state = 0;
			preItem.left = 0;
			preItem.top = 0;
			preItem.offset_x = 0;
			preItem.offset_y = 0;

			std::remove_if(preItem.desc.begin(), preItem.desc.end(), isspace); // удаляет пробелы в описании
			_itemsPre.push_back(preItem);
			pItem = pItem->NextSiblingElement("item");
		}

	}
	
	// ----------------

	tinyxml2::XMLDocument document;
	tinyxml2::XMLElement* rootElement;

	document.LoadFile("Content/Saves/save.tws");

	if (document.ErrorID() != 0)
	{
		std::cout << "Error while opening Content / Saves / save.tws file!Error: " << document.ErrorName() << std::endl;
	}
	else
	{
		rootElement = document.FirstChildElement("saves");

		tinyxml2::XMLElement* pParentElement = rootElement->FirstChildElement("inventory");

		if (pParentElement)
		{
			tinyxml2::XMLElement* pChildElement = pParentElement->FirstChildElement("item");

			if (pChildElement)
			{
				while (pChildElement != nullptr)
				{
					_inventoryItemsId.push_back(pChildElement->Attribute("id"));
					pChildElement = pChildElement->NextSiblingElement("item");
				}
			}
		}
	}


}


ItemLoader::~ItemLoader()
{
	_levelItems.clear();
}

void ItemLoader::load(std::string name)
{
	_levelItems.clear();
	_containers.clear();

	//objects on the map
	std::string path = _mapsDir + name + ".two";
	const char* charPath = path.c_str();

	tinyxml2::XMLDocument objects;
	objects.LoadFile(charPath);

	if (objects.ErrorID() != 0)
	{
		std::cout << "Error while opening " << path << " file! Error: " << objects.ErrorName() << std::endl;
	}
	else
	{
		tinyxml2::XMLElement* pMapObject = objects.FirstChildElement("object");

		while (pMapObject != nullptr)
		{
			if (pMapObject->BoolAttribute("type"))
			{
				Container tempContainer;
				std::vector<Item> tempContainerItems;

				Item containerItem;

				_itemsPre[0].left = pMapObject->FloatAttribute("left");
				_itemsPre[0].top = pMapObject->FloatAttribute("top");
				_itemsPre[0].offset_x = pMapObject->FloatAttribute("offset_x");
				_itemsPre[0].offset_y = pMapObject->FloatAttribute("offset_y");
				_itemsPre[0].state = strToBool(pMapObject->Attribute("state"));
				_itemsPre[0].need = pMapObject->Attribute("need") ? pMapObject->Attribute("need") : "";

				containerItem = makeItem(&_itemsPre[0], _itemTilesets);

				tinyxml2::XMLElement* pItem = pMapObject->FirstChildElement("item");

				while (pItem != nullptr)
				{
					Item tempContainerItem;

					for (unsigned int i = 1; i < _itemsPre.size(); i++)
					{
						if (pItem->Attribute("id") == _itemsPre[i].id)
						{
							_itemsPre[i].state = pItem->Attribute("state") ? strToBool(pItem->Attribute("state")) : false;
							tempContainerItem = makeItem(&_itemsPre[i], _itemTilesets);
						}
					}

					tempContainerItems.push_back(tempContainerItem);

					pItem = pItem->NextSiblingElement("item");
				}

				tempContainer.container = containerItem;
				tempContainer.items = tempContainerItems;

				_containers.push_back(tempContainer);
			}
			else
			{
				Item mapItem;

				for (unsigned int i = 1; i < _itemsPre.size(); i++)
				{
					if (pMapObject->Attribute("id") == _itemsPre[i].id)
					{
						_itemsPre[i].left = pMapObject->FloatAttribute("left");
						_itemsPre[i].top = pMapObject->FloatAttribute("top");
						_itemsPre[i].offset_x = pMapObject->FloatAttribute("offset_x");
						_itemsPre[i].offset_y = pMapObject->FloatAttribute("offset_y");
						_itemsPre[i].state = strToBool(pMapObject->Attribute("state"));
						_itemsPre[i].need = pMapObject->Attribute("need") ? pMapObject->Attribute("need") : "";

						mapItem = makeItem(&_itemsPre[i], _itemTilesets);
					}
				}

				_levelItems.push_back(mapItem);
			}

			pMapObject = pMapObject->NextSiblingElement("object");
		}
	}

	Item inventoryItem;

	for (unsigned int i = 0; i < _inventoryItemsId.size(); i++)
	{
		for (unsigned int j = 0; j < _itemsPre.size(); j++)
		{
			if (_itemsPre[j].id == _inventoryItemsId[i])
			{
				inventoryItem = makeItem(&_itemsPre[j], _itemTilesets);
				_inventoryItems.push_back(inventoryItem);

				break;
			}
		}
	}
}

std::vector<Item>* ItemLoader::getItems()
{
	return &_levelItems;
}

std::vector<Item>* ItemLoader::getInventoryItems()
{
	return &_inventoryItems;
}

std::vector<Container>* ItemLoader::getContainers()
{
	return &_containers;
}


Item ItemLoader::makeItem(PreItem* preItem, std::vector<ItemTileset>& tilesets)
{
	sf::Sprite sprite;

	int objectWidth = (int)preItem->width;
	int objectHeight = (int)preItem->height;;
	unsigned int tileId = preItem->tileId;
	float left = preItem->left;
	float top = preItem->top;
	unsigned short tilesetId = preItem->tileset;

	float offset_x = preItem->offset_x;
	float offset_y = preItem->offset_y;

	int tilesetWidth = tilesets[tilesetId].width / objectWidth;
	int tilesetHeight = tilesets[tilesetId].height / objectHeight;

	int spritePositionX = (tileId - tilesetWidth * (tileId / tilesetWidth)) * objectWidth;
	int spritePositionY = (tileId / tilesetWidth) * objectHeight;

	sprite.setTexture((*_pTextures)[tilesets[tilesetId].name]);
	sprite.setTextureRect(sf::IntRect(spritePositionX, spritePositionY, objectWidth, objectHeight));
	sprite.setPosition(sf::Vector2f(left * TILE_W, top * TILE_H));
	sprite.move(sf::Vector2f(offset_x, offset_y));

	std::string description = preItem->desc;
	std::string dependence = preItem->need;

	std::string id = preItem->id.c_str();
	bool itemState = preItem->state;

	// обращение к файлу сохранений, чтобы узнать, какие предметы персонаж собрал с карты
	SaveFileHandler saveFile("Content/Saves/save.tws");
	std::pair<std::string, std::string> search;
	search.first = "id";
	search.second = id;
	std::string response = saveFile.getElement("mapItems", "item", search, "state");

	if (response != "")
	{
		itemState = strToBool(response);
	}

	Item item(sprite, preItem->name, id, description, dependence);
	item.setState(itemState);

	return item;
}


bool ItemLoader::strToBool(std::string str)
{
	if (str == "1" || str == "true" || str == "TRUE")
	{
		return true;
	}

	return false;
}