#include "BaseScreen.h"

BaseScreen::BaseScreen(ContentManager* contentManager)
{
	_pContentManager = contentManager;
	_tileSize = _pContentManager->getTileSize();
}

BaseScreen::~BaseScreen()
{
	_animationManagers.clear();
	_spriteManagers.clear();
	_soundManagers.clear();
}

void BaseScreen::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
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
