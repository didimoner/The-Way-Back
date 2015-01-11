#pragma once
#include "SFML\Graphics.hpp"

#include "BaseScreen.h"
#include "MainScreen.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	void handleKeyPress(sf::Keyboard::Key key, bool isPressed);

	void update(float gameTime);
	void draw(sf::RenderWindow &window);

private:
	std::vector<BaseScreen*> _screens;
	BaseScreen* _currentScreen;

	ContentManager _contentManager;

	MainScreen* _pMainScreen;
};
