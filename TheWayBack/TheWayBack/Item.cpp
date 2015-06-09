#include "Item.h"

Item::Item()
{
}

Item::Item(sf::Sprite sprite, std::string name, std::string id, std::string desc)
{
	_sprite = sprite;
	_name = name;
	_id = id;
	_description = desc;
	_bounds = sf::FloatRect(sprite.getPosition().x, sprite.getPosition().y, 
		(float)sprite.getTextureRect().width, (float)sprite.getTextureRect().height);
	_state = true;
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