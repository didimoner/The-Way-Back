#pragma once
#include "SFML\Graphics.hpp"

#include "ContentManager.h"
#include "AnimationManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Animation.h"

class BaseScreen
{
public:
	BaseScreen(ContentManager* pContentManager, sf::Vector2u screenSize);
	~BaseScreen();

	virtual void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	virtual void handleMouse(sf::Mouse::Button key, bool pressed);
	
	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow& window);
	
	virtual void activate();
	virtual void deactivate();

	virtual bool isActivated();

	virtual short getState();

protected:
	ContentManager* _pContentManager;

	std::map <std::string, sf::Texture>* _pTextures;
	std::map <std::string, sf::SoundBuffer>* _pSounds;
	std::map <std::string, sf::Font>* _pFonts;

	short _tileSize;
	bool _isActivated;
	short _screenState;
	sf::Vector2u _screenSize;
};