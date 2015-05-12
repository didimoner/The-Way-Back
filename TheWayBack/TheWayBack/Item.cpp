#include "Item.h"

Item::Item(sf::Sprite sprite, std::string name, std::string desc)
{
	_sprite = sprite;
	_name = name;
	_description = desc;
	_bounds = sf::FloatRect(sprite.getPosition().x, sprite.getPosition().y, 
		(float)sprite.getTextureRect().width, (float)sprite.getTextureRect().height);
	_isVisible = true;
}

Item::~Item()
{
}

void Item::update(float gameTime)
{
}

void Item::draw(sf::RenderWindow &window)
{
	if (_isVisible) window.draw(_sprite);
}

std::string Item::getName()
{
	return _name;
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

void Item::setVisible(bool flag)
{
	_isVisible = flag;
}

bool Item::getState()
{
	return _isVisible;
}