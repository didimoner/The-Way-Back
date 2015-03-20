#include "Game.h"
#include <iostream>

Game::Game(sf::Vector2i resolution, std::string title, bool isFullscreen)
{
	_screenResolution = resolution;
	_title = title;
	_isFullscreen = isFullscreen;

	_window.create(sf::VideoMode(_screenResolution.x, _screenResolution.y), _title,
		_isFullscreen ? sf::Style::Fullscreen : sf::Style::Close);
	_window.setFramerateLimit(60);
	_window.setKeyRepeatEnabled(false);
	_window.setVerticalSyncEnabled(false);
	_window.setMouseCursorVisible(true);

	_screenManager = new ScreenManager(_window.getSize());
}

Game::~Game()
{
	delete _screenManager;
}

void Game::update()
{
	_gameTime = (float)_clock.getElapsedTime().asMicroseconds();
	//std::cout << "FPS: " << 1000000.0f / _clock.getElapsedTime().asMicroseconds() << std::endl;
	
	_gameTime /= 500;

	if (_gameTime > 20)
		_gameTime = 20;

	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::KeyPressed:
			if (_event.key.code == sf::Keyboard::F8)
			{
				// fullscreen
			}
			_screenManager->handleKeyboard(_event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			_screenManager->handleKeyboard(_event.key.code, false);
			break;

		case sf::Event::MouseButtonPressed:
			_screenManager->handleMouse(_event.key.code, true);
			break;

		case sf::Event::MouseButtonReleased:
			_screenManager->handleMouse(_event.key.code, false);
			break;

		default:
			break;
		}
	}

	_screenManager->update(_gameTime);
	_clock.restart();
}

void Game::draw()
{
	_window.clear(sf::Color::Black);
	_screenManager->draw(_window);
	_window.display();
}

void Game::run()
{
	while (_window.isOpen())
	{
		update();
		draw();
	}
}