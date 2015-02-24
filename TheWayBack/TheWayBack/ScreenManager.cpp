#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	_contentManager.setRootFolder("Content");
	_contentManager.setTileSize(32);
	//_contentManager.loadContent();

	_pMainScreen = new MainScreen(&_contentManager);
	_screens.push_back(_pMainScreen);

	_currentScreen = _screens[0];
}

ScreenManager::~ScreenManager()
{
	delete _pMainScreen;
}

void ScreenManager::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
{
	_currentScreen->handleKeyPress(key, isPressed);
}

void ScreenManager::update(float gameTime)
{

	_currentScreen->update(gameTime);
}

void ScreenManager::draw(sf::RenderWindow& window)
{
	_currentScreen->draw(window);
}