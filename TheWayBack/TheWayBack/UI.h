#pragma once
#include <SFML\Graphics.hpp>

class UI
{
public:
	UI();
	~UI();

	void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	void handleMouse(sf::Keyboard::Key key, bool pressed);

	void update(float gameTime);
	void draw(sf::RenderWindow &window);

private:

};

