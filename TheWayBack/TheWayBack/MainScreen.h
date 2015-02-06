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

	virtual void handleKeyPress(sf::Keyboard::Key key, bool isPressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

private:
	Player* _player;
	Animation* _animation;
	TileMapLoader* _tileMapLoader;
	std::vector<Entity*> _entities;
};
