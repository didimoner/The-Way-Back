#include "Window.h"
#include <iostream>
using namespace ui;

Window::Window()
{
}

Window::Window(float width, float height, std::string header)
{
	_size = sf::Vector2f(width, height);

	_headerText = new sf::Text();
	_headerText->setFont((*_pFonts)["Visitor"]);
	_headerText->setScale(0.5f, 0.5f);
	_headerText->setCharacterSize(28 * 2);
	_headerText->setColor(sf::Color::Black);
	_headerText->setString(header);

	_window.setSize(_size);
	_window.setOutlineColor(sf::Color::White);
	_window.setOutlineThickness(4);
	_window.setTexture(&(*_pTextures)["tekstura-tkani"]);
	_visible = false;
}

Window::~Window()
{
}

void Window::update(float gameTime)
{
}

void Window::draw(sf::RenderWindow& window)
{
	if (_visible) window.draw(_window);
}


void Window::setPosition(float x, float y)
{
	_window.setPosition(x - _size.x / 2, y - _size.y / 2);
}

sf::Vector2f Window::getSize()
{
	return _window.getSize();
}

void Window::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
	if (pressed)
	{
		switch (key)
		{
		case sf::Keyboard::I:
			_visible = _visible ? false : true;
			break;

		default:
			break;
		}
	}
	else
	{

	}

}