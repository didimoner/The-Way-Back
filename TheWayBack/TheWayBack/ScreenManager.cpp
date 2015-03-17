#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	_contentManager.setRootFolder("Content");
	_contentManager.setTileSize(32);

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

void ScreenManager::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
	if (pressed)
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
	
	_currentScreen->handleKeyboard(key, pressed);
}

void ScreenManager::handleMouse(sf::Keyboard::Key key, bool pressed)
{
	_currentScreen->handleMouse(key, pressed);
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------
void ScreenManager::update(float gameTime)
{
	if (_isSwitched)
	{
		if (_currentScreen->isActivated()) _currentScreen->deactivate();
		_currentScreen = _screens[_gameState];
		_currentScreen->activate();

		_isSwitched = false;
	}

	if (_currentScreen->getState() != _gameState)
	{
		_gameState = (GameState)_currentScreen->getState();
		_isSwitched = true;
	}
	
	_currentScreen->update(gameTime);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------
void ScreenManager::draw(sf::RenderWindow& window)
{
	_currentScreen->draw(window);
}
