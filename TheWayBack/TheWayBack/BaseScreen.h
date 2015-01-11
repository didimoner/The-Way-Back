#pragma once
#include "SFML\Graphics.hpp"

#include "ContentManager.h"
#include "AnimationManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"

class BaseScreen
{
public:
	BaseScreen(ContentManager* contentManager);
	~BaseScreen();

	virtual void handleKeyPress(sf::Keyboard::Key key, bool isPressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

protected:
	ContentManager* _pContentManager;

	std::map<std::string, AnimationManager> _animationManagers;
	std::map<std::string, SpriteManager> _spriteManagers;
	std::map<std::string, SoundManager> _soundManagers;

	std::map <std::string, sf::Texture>* _pTextures;
	std::map <std::string, sf::SoundBuffer>* _pSounds;
	sf::Font* _pFont;

	short _tileSize;
};
