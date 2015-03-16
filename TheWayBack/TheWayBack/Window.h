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
	Window(float x, float y, float width, float height);
	~Window();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

private:
	sf::Vector2f _size;
	sf::RectangleShape _window;
};

