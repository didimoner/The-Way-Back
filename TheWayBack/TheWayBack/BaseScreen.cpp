#include "BaseScreen.h"

BaseScreen::BaseScreen(ContentManager* pContentManager, sf::Vector2u screenSize)
{
	_pContentManager = pContentManager;
	_screenSize = screenSize;
	_tileSize = _pContentManager->getTileSize();
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
