#pragma once
#include "BaseScreen.h"
#include "Button.h"

class MenuScreen :
	public BaseScreen
{
public:
	MenuScreen(ContentManager *contentManager);
	~MenuScreen();

	virtual void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	virtual void handleMouse(sf::Keyboard::Key key, bool pressed);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual void activate();
	virtual void deactivate();

	virtual bool getState();

private:
	Animation* _animation;
	sf::View _camera;
	ui::Button* _button;
};

