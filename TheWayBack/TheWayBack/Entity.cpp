#include "Entity.h"
#include <iostream>

Entity::Entity(void)
{
}

Entity::~Entity(void)
{
}

void Entity::update(float gameTime)
{
}

void Entity::draw(sf::RenderWindow &window)
{
}

sf::FloatRect Entity::getBounds()
{
	return _bounds;
}

void Entity::setPosition(sf::Vector2f position)
{
	_position = position;
}