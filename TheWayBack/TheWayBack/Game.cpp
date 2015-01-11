#include "Game.h"
#include <iostream>

Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::initialize(void)
{
	_window.create(sf::VideoMode(640, 640), "The Maze");
	_window.setFramerateLimit(60);
	_window.setKeyRepeatEnabled(false);
	_window.setVerticalSyncEnabled(true);
}

void Game::loadContent(void)
{
}

void Game::update()
{
	_gameTime = (float)_clock.getElapsedTime().asMicroseconds();
	_clock.restart();

	_gameTime /= 500;

	if (_gameTime > 40)
		_gameTime = 40;

	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::KeyPressed:
			_screenManager.handleKeyPress(_event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			_screenManager.handleKeyPress(_event.key.code, false);
			break;

		default:
			break;
		}
	}

	_screenManager.update(_gameTime);
}

void Game::draw()
{
	_window.clear();
	_screenManager.draw(_window);
	_window.display();
}

void Game::run()
{
	initialize();
	loadContent();

	while (_window.isOpen())
	{
		update();
		draw();
	}
}