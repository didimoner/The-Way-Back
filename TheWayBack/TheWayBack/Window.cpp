#include "Window.h"
using namespace ui;

Window::Window()
{
}

Window::Window(float x, float y, float width, float height)
{
	_position = sf::Vector2f(x, y);
	_size = sf::Vector2f(width, height);

	_window.setSize(_size);
	_window.setPosition(_position);
}

Window::~Window()
{
}

void Window::update(float gameTime)
{
}

void Window::draw(sf::RenderWindow& window)
{
	window.draw(_window);
}
