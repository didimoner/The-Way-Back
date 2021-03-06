#pragma once
#include "SFML\Graphics.hpp"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);
	virtual sf::FloatRect getBounds();
	virtual void setPosition(sf::Vector2f position);

protected:
	sf::Vector2f _position;
	sf::Vector2i _size;
	sf::FloatRect _bounds;
};
