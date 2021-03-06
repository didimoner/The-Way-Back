#pragma once

#include "BaseScreen.h"
#include "Player.h"
#include "TileMapLoader.h"
#include "ItemLoader.h"
#include "Window.h"

class MainScreen :
	public BaseScreen
{
public:
	MainScreen(sf::Vector2u screenSize);
	~MainScreen();

	virtual void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	virtual void handleMouse(sf::Keyboard::Key key, bool pressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual void activate();
	virtual void deactivate();

	virtual bool isActivated();

private:
	std::map<std::string, AnimationManager> _animationManagers;
	std::map<std::string, SpriteManager> _spriteManagers;
	std::map<std::string, SoundManager> _soundManagers;
	std::vector<ui::UIObject*> _uiObjects;

	Player* _player;
	TileMapLoader* _tileMapLoader;
	ItemLoader* _itemLoader;
	std::vector<Entity*> _entities;
	sf::View _camera;
	sf::Vector2f _cameraSpeed;
	Inventory* _pInventory;
	bool _mapChanged;
	std::vector<std::vector<std::vector<sf::Sprite>>>* _currentMapSprites;
	std::vector<Item>* _levelItems;
	std::vector<Container>* _containers;
	sf::Music* _bgMusic;
};
