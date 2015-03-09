#pragma once
#include "BaseScreen.h"
class MenuScreen :
	public BaseScreen
{
public:
	MenuScreen(ContentManager *contentManager);
	~MenuScreen();

	virtual void handleKeyPress(sf::Keyboard::Key key, bool isPressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual void activate();
	virtual void deactivate();

	virtual bool getState();

private:
	Animation* _animation;
	sf::View _camera;
};

