#pragma once
#include "UIObject.h"

namespace ui
{
	class Window;
}

class ui::Window :
	public ui::UIObject
{
public:
	Window();
	Window(float width, float height, std::string header);
	~Window();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);
	void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	virtual void setPosition(float x, float y);

	sf::Vector2f getSize();

protected:
	sf::Vector2f _size;
	sf::RectangleShape _window;
	bool _visible;
	sf::Text* _headerText;
	sf::Vector2f _textOffset;
};

