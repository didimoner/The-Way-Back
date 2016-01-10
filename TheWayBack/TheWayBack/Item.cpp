#include "Item.h"
#include <iostream>

Item::Item()
{
}

Item::Item(sf::Sprite sprite, std::string name, std::string id, std::string desc, std::string dependence)
{
	_sprite = sprite;
	_name = name;
	_id = id;
	_description = desc;
	_bounds = sf::FloatRect(sprite.getPosition().x, sprite.getPosition().y, 
		(float)sprite.getTextureRect().width, (float)sprite.getTextureRect().height);
	_state = true;
	parseDependence(dependence);
}

Item::~Item()
{
}

void Item::update(float gameTime)
{
}

void Item::draw(sf::RenderWindow &window)
{
	if (_state) window.draw(_sprite);
}

std::string Item::getName()
{
	return _name;
}

std::string Item::getId()
{
	return _id;
}

std::string Item::getDescription()
{
	return _description;
}

sf::Sprite* Item::getSprite()
{
	return &_sprite;
}

sf::FloatRect Item::getBounds()
{
	return _bounds;
}

void Item::setState(bool flag)
{
	_state = flag;
}

bool Item::getState()
{
	return _state;
}

std::vector<std::string>* Item::getDependence()
{
	return &_dependence;
}

void Item::parseDependence(std::string dependence)
{
	std::string sep(",");

	while (true)
	{
		if (dependence.length() <= 0) break;

		std::string::size_type pos = dependence.find(sep);
		_dependence.push_back(dependence.substr(0, pos));

		if (pos > dependence.length()) break;
		dependence = dependence.substr(pos + sep.length());
	}
}

void Item::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Item::setScale(float x, float y)
{
	_sprite.setScale(x, y);
}

