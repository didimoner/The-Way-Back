#include "BaseScreen.h"

BaseScreen::BaseScreen(ContentManager* pContentManager)
{
	_pContentManager = pContentManager;
	_tileSize = _pContentManager->getTileSize();
}

BaseScreen::~BaseScreen()
{
}

void BaseScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
}

void BaseScreen::handleMouse(sf::Keyboard::Key key, bool pressed)
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
