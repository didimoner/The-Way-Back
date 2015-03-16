#pragma once
#include "UIObject.h"

namespace ui
{
	class Button;
}

class ui::Button :
	public ui::UIObject
{
public:
	Button();
	Button(float x, float y, float width, float height, sf::Text text);
	~Button();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	void setText(sf::Text text);
	void setOffset(float x, float y);

	void handleMouse(sf::Keyboard::Key key, bool pressed);

	bool getState();

private:
	sf::Vector2f _size;
	sf::RectangleShape _button;
	sf::Text _text;
	sf::Vector2f _offset;
	bool _hover;
	bool _isClicked;

	void handleIntersection(sf::RenderWindow& window);
};

