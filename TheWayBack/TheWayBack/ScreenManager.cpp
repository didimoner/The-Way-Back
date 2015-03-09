#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	_contentManager.setRootFolder("Content");
	_contentManager.setTileSize(32);
	//_contentManager.loadContent();

	_pSplashScreen = new SplashScreen(&_contentManager);
	_screens.push_back(_pSplashScreen);

	_pMenuScreen = new MenuScreen(&_contentManager);
	_screens.push_back(_pMenuScreen);

	_pMainScreen = new MainScreen(&_contentManager);
	_screens.push_back(_pMainScreen);

	_gameState = GameState::G_SPLASHSCREEN;
	_currentScreen = _screens[_gameState];

	_isSwitched = true;
}

ScreenManager::~ScreenManager()
{
	delete _pSplashScreen;
	delete _pMenuScreen;
	delete _pMainScreen;
}

void ScreenManager::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
{
	if (isPressed)
	{
		if (_gameState != 0)
		{
			switch (key)
			{
			case sf::Keyboard::Escape:
				_gameState = _gameState == 2 ? GameState::G_MENU : GameState::G_PLAY;
				_isSwitched = true;
				break;

			default:
				break;
			}
		}
		else
		{
			_gameState = GameState::G_MENU;
			_isSwitched = true;
		}
	}
	
	_currentScreen->handleKeyPress(key, isPressed);
}

void ScreenManager::update(float gameTime)
{
	if (_isSwitched)
	{
		if (_currentScreen->getState()) _currentScreen->deactivate();
		_currentScreen = _screens[_gameState];
		_currentScreen->activate();

		_isSwitched = false;
	}
	
	_currentScreen->update(gameTime);
}

void ScreenManager::draw(sf::RenderWindow& window)
{
	_currentScreen->draw(window);
}