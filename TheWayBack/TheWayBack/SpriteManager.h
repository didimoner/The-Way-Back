#pragma once
#include "SFML\Graphics.hpp"

class SpriteManager
{
public:
	SpriteManager(void);
	SpriteManager(sf::Texture &texture, short tileSize);
	~SpriteManager(void);

	void draw(sf::RenderWindow& window);

	void addSprite(std::string name, sf::Vector2f position);
	void addSprite(std::string name, sf::Vector2f position, sf::Vector2i textureRect);

	void setPosition(std::string name, float x, float y);
	sf::Vector2f getPosition(std::string name);

	void setOffset(std::string name, float x, float y);

private:
	sf::Sprite _sprite;
	std::map<std::string, sf::Sprite> _sprites;
	short _tileSize;
};
