#include "SaveFileHandler.h"

SaveFileHandler::SaveFileHandler(char* path)
{
	_path = path;
	_document.LoadFile(_path);

	if (_document.ErrorID() != 0)
	{
		tinyxml2::XMLNode* pRoot = _document.NewElement("saves");
		_document.InsertEndChild(pRoot);

		save();
	}

	_pRootElement = _document.FirstChildElement("saves");
}


SaveFileHandler::~SaveFileHandler()
{
}

void SaveFileHandler::addElement(SaveElement parent, SaveElement child)
{
	tinyxml2::XMLElement* pParentElement = _pRootElement->FirstChildElement(parent.name);

	if (!pParentElement)
	{
		tinyxml2::XMLElement* pItem = _document.NewElement(parent.name);

		if (parent.attributes.size() > 0)
		{
			for (const auto& elements : parent.attributes)
			{
				pItem->SetAttribute(elements.first.c_str(), elements.second.c_str());
			}
		}

		_pRootElement->InsertEndChild(pItem);
	}

	// -----------

	if (child.name != "")
	{
		bool exists = false;

		pParentElement = _pRootElement->FirstChildElement(parent.name);
		tinyxml2::XMLElement* pChildElement = pParentElement->FirstChildElement(child.name);
		while (pChildElement != nullptr)
		{
			// проверка на существование
			if (pChildElement->Attribute(child.attrForSearch.first.c_str()))
			{
				if (!strcmp(pChildElement->Attribute(child.attrForSearch.first.c_str()), child.attrForSearch.second.c_str()))
				{
					exists = true;
					break;
				}
			}

			pChildElement = pChildElement->NextSiblingElement(child.name);
		}

		if (!exists)
		{
			tinyxml2::XMLElement* pItem = _document.NewElement(child.name);

			if (child.attributes.size() > 0)
			{
				for (const auto& elements : child.attributes)
				{
					pItem->SetAttribute(elements.first.c_str(), elements.second.c_str());
				}
			}

			pParentElement->InsertEndChild(pItem);
		}
	}

	save();
}

bool SaveFileHandler::deleteElement(char* parentElement, char* childElement, std::pair<std::string, std::string> search)
{
	tinyxml2::XMLElement* pParentElement = _pRootElement->FirstChildElement(parentElement);

	if (pParentElement)
	{
		if (!strcmp(childElement, ""))
		{
			if (search.first == "" & search.second == "")
			{
				_pRootElement->DeleteChild(pParentElement);
				save();
				return 0;
			}
			else if (!strcmp(pParentElement->Attribute(search.first.c_str()), search.second.c_str()))
			{
				_pRootElement->DeleteChild(pParentElement);
				save();
				return 0;
			}
		}
		else
		{
			tinyxml2::XMLElement* pChildElement = pParentElement->FirstChildElement(childElement);

			if (pChildElement)
			{
				while (pChildElement != nullptr)
				{
					if (!strcmp(pChildElement->Attribute(search.first.c_str()), search.second.c_str()))
					{
						pParentElement->DeleteChild(pChildElement);
						save();
						return 0;
					}

					pChildElement = pChildElement->NextSiblingElement(childElement);
				}
			}
		}
	}
	
	return 1;
}

std::string SaveFileHandler::getElement(char* parentElement, char* childElement, std::pair<std::string, std::string> search, char* target)

{
	tinyxml2::XMLElement* pParentElement = _pRootElement->FirstChildElement(parentElement);
	if (!pParentElement) return "";

	tinyxml2::XMLElement* pChildElement = pParentElement->FirstChildElement(childElement);

	if (pChildElement)
	{
		while (pChildElement != nullptr)
		{
			if (!strcmp(pChildElement->Attribute(search.first.c_str()), search.second.c_str()))
			{
				return pChildElement->Attribute(target) ? pChildElement->Attribute(target) : "";
			}

			pChildElement = pChildElement->NextSiblingElement(childElement);
		}
	}
	else
	{
		return pParentElement->Attribute(target) ? pParentElement->Attribute(target) : "";
	}

	

	return "";
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


