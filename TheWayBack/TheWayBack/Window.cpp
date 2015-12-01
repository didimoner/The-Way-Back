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
	_headerText->setCharacterSize(36 * 2);
	_headerText->setString(header);
	_headerText->setColor(sf::Color::Color(50, 50, 50));
	_textOffset = sf::Vector2f(_headerText->getGlobalBounds().width / 2.f, (_headerText->getCharacterSize() / 2) / 6.f);

	_window.setSize(_size);
	_window.setOutlineColor(sf::Color::White);
	_window.setOutlineThickness(4);
	_window.setTexture(&(*_pTextures)["tekstura-tkani"]);
	_visible = false;
}

Window::~Window()
{
	delete _headerText;
}

void Window::update(float gameTime)
{
}

void Window::draw(sf::RenderWindow& window)
{
	if (_visible) window.draw(_window);
	if (_visible) window.draw(*_headerText);
}


void Window::setPosition(float x, float y)
{
	_headerText->setPosition(sf::Vector2f(x - _textOffset.x, y - (_size.y / 2 + _textOffset.y)));
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