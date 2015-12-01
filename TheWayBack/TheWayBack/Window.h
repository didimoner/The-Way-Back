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

	void update(float gameTime);
	void draw(sf::RenderWindow &window);
	void handleKeyboard(sf::Keyboard::Key key, bool pressed);
	void setPosition(float x, float y);

	sf::Vector2f getSize();

protected:
	sf::Vector2f _size;
	sf::RectangleShape _window;
	bool _visible;
	sf::Text* _headerText;
	sf::Vector2f _textOffset;
};

