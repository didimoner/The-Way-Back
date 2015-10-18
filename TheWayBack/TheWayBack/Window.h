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
	Window(float width, float height);
	~Window();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	void setPosition(float x, float y);
	sf::Vector2f getSize();

private:
	sf::Vector2f _size;
	sf::RectangleShape _window;
};

