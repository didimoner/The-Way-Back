#include "BaseScreen.h"

BaseScreen::BaseScreen(ContentManager* contentManager)
{
	_pContentManager = contentManager;
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

void BaseScreen::draw(sf::RenderWindow &window)
{
}

void BaseScreen::activate()
{
}

void BaseScreen::deactivate()
{
}

bool BaseScreen::getState()
{
	return _isActivated;
}
