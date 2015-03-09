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
	G_PLAY,
	G_PAUSE
};

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
	GameState _gameState;

	SplashScreen* _pSplashScreen;
	MenuScreen* _pMenuScreen;
	MainScreen* _pMainScreen;

	bool _isSwitched;
	bool _forceSwitch;
};
