#include "UIObject.h"
using namespace ui;

UIObject::UIObject()
{
	_contentManager.setRootFolder("Content");
	_contentManager.setTileSize(32);

	_contentManager.loadContent("ui");
	_pTextures = _contentManager.getTextures();
	_pSounds = _contentManager.getSounds();
	_pFonts = _contentManager.getFonts();
}


UIObject::~UIObject()
{
	_contentManager.clear();
}

void UIObject::update(float gameTime)
{
}

void UIObject::draw(sf::RenderWindow& window)
{
}

void UIObject::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
}

void UIObject::setPosition(float x, float y)
{
}