#pragma once
#include "BaseScreen.h"
class SplashScreen :
	public BaseScreen
{
public:
	SplashScreen(ContentManager *contentManager);
	~SplashScreen();

	virtual void handleKeyPress(sf::Keyboard::Key key, bool isPressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual void activate();
	virtual void deactivate();

	virtual bool isActivated();
	virtual short getState();

private:
	sf::Sprite _splashSprite;
	sf::RectangleShape _blackRect;
	short _blackRectTransperency;
	float _splashDuration;
	sf::Clock _clock;
};

