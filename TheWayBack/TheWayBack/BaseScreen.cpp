#include "BaseScreen.h"

BaseScreen::BaseScreen(ContentManager* contentManager)
{
	_pContentManager = contentManager;
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_pFont = _pContentManager->getFont();
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