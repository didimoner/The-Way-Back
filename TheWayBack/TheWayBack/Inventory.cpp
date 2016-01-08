#include "Inventory.h"
#include <iostream>

Inventory::Inventory(unsigned short size, float width, float height, std::string header, TileMapLoader* tileMapLoader) :
	ui::Window(width, height, header)
{
	_size = size;
	_pTileMapLoader = tileMapLoader;

	_grid = new sf::Sprite((*_pTextures)["grid"]);
	_grid->setScale(0.7f, 0.7f);

	_gridOffset = sf::Vector2f(_grid->getGlobalBounds().width / 2.f, (_grid->getTextureRect().height * _grid->getScale().y) / 6.f);

	loadItems();

}

// TODO: �������� ��������� �� �����

Inventory::~Inventory()
{
	delete _window;
}

void Inventory::update(float gameTime)
{
	
}

void Inventory::draw(sf::RenderWindow& window)
{
	if (_visible)
	{
		window.draw(Window::_window);
		window.draw(*_headerText);
		window.draw(*_grid);

		for (unsigned int i = 0; i < _cells.size(); i++)
		{
			_cells[i].setState(true);
			_cells[i].setScale(2.f, 2.f);
			_cells[i].draw(window);
		}

	}
}

void Inventory::setPosition(float x, float y)
{
	_headerText->setPosition(sf::Vector2f(x - _textOffset.x, y - (Window::_size.y / 2 + _textOffset.y)));
	_grid->setPosition(sf::Vector2f(x - _gridOffset.x, y - _gridOffset.y));
	Window::_window.setPosition(x - Window::_size.x / 2, y - Window::_size.y / 2);

	for (unsigned int i = 0; i < _cells.size(); i++)
	{
		 _cells[i].setPosition(sf::Vector2f(x - _gridOffset.x + i * 72 + 8, y - _gridOffset.y + 8));
	}

}

void Inventory::add(Item* item)
{
	if (_cells.size() <= _size)
	{
		bool exists = false;
		for (unsigned int i = 0; i < _cells.size(); i++)
		{
			if (_cells[i].getId() == item->getId())
			{
				exists = true;
				break;
			}
		}

		if (!exists)
		{
			_cells.push_back(*item);
			std::cout << "Item added: " << item->getName() << std::endl;
		}
	}
}

int Inventory::getSize()
{
	return _size;
}

bool Inventory::contains(std::string seed, int mode)
{
	for (unsigned int i = 0; i < _cells.size(); i++)
	{
		switch (mode)
		{
		case 0:
			if (_cells[i].getName() == seed) return true;
		case 1: 
			if (_cells[i].getId() == seed) return true;
		default:
			break;
		}
	}

	return false;
}

void Inventory::loadItems()
{
	std::vector<Item>* pItems = _pTileMapLoader->getItems();

	tinyxml2::XMLDocument document;
	tinyxml2::XMLElement* rootElement;

	document.LoadFile("Content/Saves/save.tws");

	if (document.ErrorID() != 0)
	{
		return;
	}

	rootElement = document.FirstChildElement("saves");

	tinyxml2::XMLElement* pParentElement = rootElement->FirstChildElement("inventory");

	if (!pParentElement) return;

	tinyxml2::XMLElement* pChildElement = pParentElement->FirstChildElement("item");


	if (pChildElement)
	{
		while (pChildElement != nullptr)
		{
			for (unsigned int i = 0; i < pItems->size(); i++)
			{
				if ((*pItems)[i].getId() == pChildElement->Attribute("id"))
				{
					std::cout << "Match! " << (*pItems)[i].getId() << " : " << pChildElement->Attribute("id") << std::endl;
					_cells.push_back((*pItems)[i]);
				}
			}

			pChildElement = pChildElement->NextSiblingElement("item");
		}
	}
}
