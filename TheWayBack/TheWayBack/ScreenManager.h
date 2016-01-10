#pragma once
#include "SFML\Graphics.hpp"

#include "BaseScreen.h"
#include "MainScreen.h"
#include "SplashScreen.h"
#include "MenuScreen.h"

enum GameState
{
	G_SPLASHSCREEN,
	G_MENU,
	G_PLAY
};

class ScreenManager
{
public:
	ScreenManager(sf::Vector2u screenSize);
	~ScreenManager();

	void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	void handleMouse(sf::Mouse::Button key, bool pressed);
	
	void update(float gameTime);
	void draw(sf::RenderWindow &window);

private:
	sf::Vector2u _screenSize;
	std::vector<BaseScreen*> _screens;
	BaseScreen* _currentScreen;
	GameState _gameState;

	SplashScreen* _pSplashScreen;
	MenuScreen* _pMenuScreen;
	MainScreen* _pMainScreen;

	bool _isSwitched;
	bool _forceSwitch;

};
