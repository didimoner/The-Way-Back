#pragma once
#include "SFML\Graphics.hpp"

#include "ScreenManager.h"

class Game
{
public:
	Game(sf::Vector2i resolution, std::string title, bool isFullscreen);
	~Game();

	void update();
	void draw();
	void run();

private:
	sf::Vector2i _screenResolution;
	std::string _title;
	bool _isFullscreen;

	sf::RenderWindow _window;
	sf::View _view;
	sf::Event _event;
	sf::Clock _clock;
	float _gameTime;

	ScreenManager* _screenManager;
};
