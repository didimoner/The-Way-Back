#pragma once

#include "SFML\Graphics.hpp"

//#include "ContentManager.h"
#include "ScreenManager.h"

class Game
{
public:
	Game(void);
	~Game(void);

	void initialize(void);
	void loadContent(void);
	void update(void);
	void draw(void);
	void run(void);

private:
	sf::RenderWindow _window;
	sf::Event _event;
	sf::Clock _clock;
	float _gameTime;

	ScreenManager _screenManager;
};
