#include "Window.h"
using namespace ui;

Window::Window()
{
}

Window::Window(float width, float height)
{
	_size = sf::Vector2f(width, height);

	_window.setSize(_size);
	_window.setFillColor(sf::Color::Blue);
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


void Window::setPosition(float x, float y)
{
	_window.setPosition(x, y);
}

sf::Vector2f Window::getSize()
{
	return _window.getSize();
}