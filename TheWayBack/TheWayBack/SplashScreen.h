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

	virtual bool getState();

private:
	Animation* _animation;
};

