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
	Button(float x, float y, float width, float height, std::wstring text);
	~Button();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	void setText(sf::Text text);
	void setOffset(float x, float y);

	void handleMouse(sf::Mouse::Button key, bool pressed);

	bool getState();

private:
	sf::Vector2f _size;
	sf::RectangleShape _button;
	sf::Text _text;
	sf::Vector2f _offset;
	bool _hover;
	bool _isClicked;
	sf::Vector2f _mouseLocalPosition;

	void handleIntersection(sf::RenderWindow& window);
};

