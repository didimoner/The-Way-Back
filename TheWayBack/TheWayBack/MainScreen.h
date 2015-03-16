#pragma once

#include "basescreen.h"
#include "Player.h"
#include "TileMapLoader.h"

class MainScreen :
	public BaseScreen
{
public:
	MainScreen(ContentManager *contentManager);
	~MainScreen();

	virtual void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	virtual void handleMouse(sf::Keyboard::Key key, bool pressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual void activate();
	virtual void deactivate();

	virtual bool getState();

private:
	std::map<std::string, AnimationManager> _animationManagers;
	std::map<std::string, SpriteManager> _spriteManagers;
	std::map<std::string, SoundManager> _soundManagers;

	Player* _player;
	TileMapLoader* _tileMapLoader;
	std::vector<Entity*> _entities;
	sf::View _camera;
	sf::Vector2f _cameraSpeed;
};
