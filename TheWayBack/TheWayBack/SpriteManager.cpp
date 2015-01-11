#include "SpriteManager.h"

SpriteManager::SpriteManager(void)
{
}

SpriteManager::SpriteManager(sf::Texture &texture, short tileSize)
{
	_sprite.setTexture(texture);
	_tileSize = tileSize;
}

SpriteManager::~SpriteManager(void)
{
	_sprites.clear();
}

void SpriteManager::draw(sf::RenderWindow& window)
{
	for each(std::pair<std::string, sf::Sprite> items in _sprites)
	{
		window.draw(items.second);
	}
}

void SpriteManager::addSprite(std::string name, sf::Vector2f position)
{
	_sprite.setPosition(position.x * _tileSize, position.y * _tileSize);
	_sprites[name] = _sprite;
}

void SpriteManager::addSprite(std::string name, sf::Vector2f position, sf::Vector2i textureRect)
{
	_sprite.setTextureRect(sf::IntRect(textureRect.x * _tileSize, textureRect.y * _tileSize, _tileSize, _tileSize));
	_sprite.setPosition(position.x * _tileSize, position.y * _tileSize);
	_sprites[name] = _sprite;
}

void SpriteManager::setPosition(std::string name, float x, float y)
{
	_sprites[name].setPosition(x * _tileSize, y * _tileSize);
}
sf::Vector2f SpriteManager::getPosition(std::string name)
{
	return _sprites[name].getPosition();
}

void SpriteManager::setOffset(std::string name, float x, float y)
{
	_sprites[name].move(x, y);
}