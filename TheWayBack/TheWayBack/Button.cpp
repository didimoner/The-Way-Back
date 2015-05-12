#include "Button.h"
using namespace ui;

Button::Button()
{
}

Button::Button(float x, float y, float width, float height, sf::Text text)
{
	_text = text;
	_position = sf::Vector2f(x, y);
	_size = sf::Vector2f(width, height);
	_offset = sf::Vector2f(_text.getGlobalBounds().width / 2.f, (_text.getCharacterSize() / 2) / 1.35f);
	_hover = false;
	_isClicked = false;

	_button.setSize(_size);
	_button.setPosition(_position);
	_button.setFillColor(sf::Color::Color(248, 248, 248));
	_button.setOutlineThickness(2);
	_button.setOutlineColor(sf::Color::Color(180, 180, 180));

	_text.setPosition(sf::Vector2f(x + (width / 2 - _offset.x), y + (height / 2 - _offset.y)));
	_text.setColor(sf::Color::Color(50, 50, 50));
}

Button::~Button()
{
}

void Button::update(float gameTime)
{
}

void Button::draw(sf::RenderWindow& window)
{
	handleIntersection(window);

	window.draw(_button);
	window.draw(_text);
}


void Button::setText(sf::Text text)
{
	_text = text;
}

void Button::handleMouse(sf::Mouse::Button key, bool pressed)
{
	if (_hover && sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
	{
		_button.setFillColor(sf::Color::Color(180, 180, 180));
		_text.setColor(sf::Color::White);
	}
	else
	{
		_button.setFillColor(sf::Color::Color(248, 248, 248));
		_text.setColor(sf::Color::Color(50, 50, 50));
	}

	if (_hover && !pressed)
	{
		switch (key)
		{
		case 0:
			_isClicked = true;
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
		
	}
}

void Button::handleIntersection(sf::RenderWindow& window)
{
	sf::Vector2f mouseLocalPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (_button.getGlobalBounds().contains(mouseLocalPosition.x, mouseLocalPosition.y))
	{
		_hover = true;
	}
	else
	{
		_hover = false;
	}
}

bool Button::getState()
{
	if (_isClicked)
	{
		_isClicked = false;
		return true;
	}
	
	return false;
}