#pragma once
#include <SFML\Graphics.hpp>

namespace ui
{
	class UIObject;
}

class ui::UIObject
{
public:
	UIObject();
	~UIObject();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

protected:
	sf::Vector2f _position;
};