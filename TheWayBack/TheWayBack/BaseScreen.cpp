#include "BaseScreen.h"

BaseScreen::BaseScreen(sf::Vector2u screenSize)
{
	_contentManager.setRootFolder("Content");
	_contentManager.setTileSize(32);

	_screenSize = screenSize;
	_tileSize = 32;
	_isActivated = false;
}

BaseScreen::~BaseScreen()
{
}

void BaseScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
}

void BaseScreen::handleMouse(sf::Mouse::Button key, bool pressed)
{
}

void BaseScreen::update(float gameTime)
{
}

void BaseScreen::draw(sf::RenderWindow& window)
{
}

void BaseScreen::activate()
{
}

void BaseScreen::deactivate()
{
}

bool BaseScreen::isActivated()
{
	return _isActivated;
}

short BaseScreen::getState()
{
	return _screenState;
}
