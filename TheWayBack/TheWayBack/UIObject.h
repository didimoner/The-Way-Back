#pragma once
#include <SFML\Graphics.hpp>
#include "ContentManager.h"

namespace ui
{
	class UIObject;
}

class ui::UIObject
{
public:
	UIObject();
	~UIObject();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);
	virtual void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	virtual void setPosition(float x, float y);

protected:
	sf::Vector2f _position;
	ContentManager _contentManager;

	std::map <std::string, sf::Texture>* _pTextures;
	std::map <std::string, sf::SoundBuffer>* _pSounds;
	std::map <std::string, sf::Font>* _pFonts;
};