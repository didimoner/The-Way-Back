#include "SaveFileHandler.h"

SaveFileHandler::SaveFileHandler(char* path)
{
	_path = path;
}


SaveFileHandler::~SaveFileHandler()
{
}

bool SaveFileHandler::load()
{
	_document.LoadFile(_path);

	if (_document.ErrorID() != 0)
	{
		tinyxml2::XMLNode* pRoot = _document.NewElement("saves");
		_document.InsertEndChild(pRoot);

		tinyxml2::XMLNode* pNewNode = _document.NewElement("inventory");
		pRoot->InsertEndChild(pNewNode);

		pNewNode = _document.NewElement("mapItems");
		pRoot->InsertEndChild(pNewNode);

		save();
	}

	return 0;
}

void SaveFileHandler::inventoryItemChange(Item* item)
{
	tinyxml2::XMLElement* pRootElement = _document.FirstChildElement("saves");
	tinyxml2::XMLElement* pInventory = pRootElement->FirstChildElement("inventory");

	tinyxml2::XMLElement* pItem = pInventory->FirstChildElement("item");
	while (pItem != nullptr)
	{
		if (pItem->Attribute("id") == item->getId())
		{
			std::cout << "Exists!" << std::endl;
			return;
		}

		pItem = pItem->NextSiblingElement("item");
	}

	tinyxml2::XMLElement* pNewItem = _document.NewElement("item");
	pNewItem->SetAttribute("id", item->getId().c_str());
	pInventory->InsertEndChild(pNewItem);
	
	save();
}

void SaveFileHandler::maplItemChange(Item* item, char* state)
{
	tinyxml2::XMLElement* pRootElement = _document.FirstChildElement("saves");
	tinyxml2::XMLElement* pMapItems = pRootElement->FirstChildElement("mapItems");

	bool exists = false;

	tinyxml2::XMLElement* pItem = pMapItems->FirstChildElement("item");
	while (pItem != nullptr)
	{
		if (pItem->Attribute("id") == item->getId())
		{
			pItem->SetAttribute("id", item->getId().c_str());
			pItem->SetAttribute("state", state);

			exists = true;
			break;
		}

		pItem = pItem->NextSiblingElement("item");
	}

	if (!exists)
	{
		tinyxml2::XMLElement* pItem = _document.NewElement("item");
		pItem->SetAttribute("id", item->getId().c_str());
		pItem->SetAttribute("state", state);
		pMapItems->InsertEndChild(pItem);
	}

	save();
}

bool SaveFileHandler::del(char* element, std::string id)
{
	tinyxml2::XMLElement* pRootElement = _document.FirstChildElement("saves");
	tinyxml2::XMLElement* pElement = pRootElement->FirstChildElement(element);
	tinyxml2::XMLElement* pItem = pElement->FirstChildElement("item");

	while (pItem != nullptr)
	{
		if (pItem->Attribute("id") == id)
		{
			pElement->DeleteChild(pItem);
			save();
			return 0;
		}

		pItem = pItem->NextSiblingElement("item");
	}

	return 1;
}

std::string SaveFileHandler::getElement(char* element, std::string id, char* attr)
{
	tinyxml2::XMLElement* pRootElement = _document.FirstChildElement("saves");
	tinyxml2::XMLElement* pElement = pRootElement->FirstChildElement(element);
	tinyxml2::XMLElement* pItem = pElement->FirstChildElement("item");

	while (pItem != nullptr)
	{
		if (pItem->Attribute("id") == id)
		{
			return pItem->Attribute(attr) ? pItem->Attribute(attr) : "NO_ATTR";
		}

		pItem = pItem->NextSiblingElement("item");
	}

	return "NO_ITEM";
}

bool SaveFileHandler::save()
{
	tinyxml2::XMLError eResult = _document.SaveFile(_path);

	if (eResult != tinyxml2::XML_SUCCESS)
	{
		printf("Error: %i\n", eResult);
		return 1;
	}

	return 0;
}