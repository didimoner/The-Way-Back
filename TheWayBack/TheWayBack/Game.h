#pragma once

#include "SFML\Graphics.hpp"

//#include "ContentManager.h"
#include "ScreenManager.h"

class Game
{
public:
	Game(sf::Vector2i resolution, std::string title, bool isFullscreen);
	~Game(void);

	void initialize(void);
	void loadContent(void);
	void update(void);
	void draw(void);
	void run(void);

private:
	sf::Vector2i _screenResolution;
	std::string _title;
	bool _isFullscreen;

	sf::RenderWindow _window;
	sf::View _view;
	sf::Event _event;
	sf::Clock _clock;
	float _gameTime;

	ScreenManager _screenManager;
};
