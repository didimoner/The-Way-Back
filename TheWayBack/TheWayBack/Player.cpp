#include "Player.h"
#include <iostream>

Player::Player(AnimationManager animationManager, SoundManager soundManager, float speed,
	sf::Vector2f position, sf::Vector2i size, short tileSize)
{
	_character = animationManager;
	_sounds = soundManager;
	_movementSpeed = speed / 100;
	_position = position;
	_size = size;
	_state = STAY;
	_tileSize = tileSize;
	_currentAnimation = _character.getCurrentAnimation();
	_character.setPosition(_position.x, _position.y);
	_bounds = sf::FloatRect(_position.x * _tileSize, _position.y * _tileSize, (float)_size.x, (float)_size.y);
	_isIntersecting = false;
}

Player::~Player(void)
{
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void Player::update(float gameTime, sf::View& camera, TileMapLoader& tileMapLoader)
{
	handleLiveInput();
	
	switch (_state)
	{
	case STAY:
		_character.stopAnimation(_currentAnimation);
		_character.update(gameTime);
		return;

	case WALK_UP:
		_character.setCurrentAnimation("walk_up");
		_character.playAnimation(_currentAnimation);
		move(0, -1, gameTime, tileMapLoader);
		break;

	case WALK_DOWN:
		_character.setCurrentAnimation("walk_down");
		_character.playAnimation(_currentAnimation);
		move(0, 1, gameTime, tileMapLoader);
		break;

	case WALK_LEFT:
		_character.setCurrentAnimation("walk_left");
		_character.playAnimation(_currentAnimation);
		move(-1, 0, gameTime, tileMapLoader);
		break;

	case WALK_RIGHT:
		_character.setCurrentAnimation("walk_right");
		_character.playAnimation(_currentAnimation);
		move(1, 0, gameTime, tileMapLoader);
		break;

	default:
		_character.pauseAnimation(_currentAnimation);
		break;
	}

	_character.update(gameTime);
	_currentAnimation = _character.getCurrentAnimation();

	// устанавливаем вьюху и не пускаем ее за границы карты (иначе рисовальщик выйдет за границы массива)
	sf::Vector2f cameraCenter = sf::Vector2f(_character.getPosition().x + _size.x / 2, _character.getPosition().y + _size.y / 2);

	if (tileMapLoader.getSize().x < camera.getSize().x)
	{
		cameraCenter.x = camera.getSize().x / 2 - (camera.getSize().x - tileMapLoader.getSize().x) / 2;
	}
	else
	{
		if ((cameraCenter.x - camera.getSize().x / 2) < 0)
		{
			cameraCenter.x = camera.getSize().x / 2;
		}

		if ((cameraCenter.x + camera.getSize().x / 2) >= tileMapLoader.getSize().x)
		{
			cameraCenter.x = tileMapLoader.getSize().x - camera.getSize().x / 2;
		}
		
	}

	if (tileMapLoader.getSize().y < camera.getSize().y)
	{
		cameraCenter.y = camera.getSize().y / 2 - (camera.getSize().y - tileMapLoader.getSize().y) / 2;
	}
	else
	{
		
		if ((cameraCenter.y - camera.getSize().y / 2) < 0)
		{
			cameraCenter.y = camera.getSize().y / 2;
		}

		if ((cameraCenter.y + camera.getSize().y / 2) >= tileMapLoader.getSize().y)
		{
			cameraCenter.y = tileMapLoader.getSize().y - camera.getSize().y / 2;
		}
	}

	camera.setCenter(cameraCenter.x, cameraCenter.y);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void Player::draw(sf::RenderWindow& window)
{
	_character.draw(window);
}

// -----------------------------------------------------

void Player::handleKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::B:
		_sounds.play("jump");
		break;

	default:
		break;
	}
}

void Player::handleKeyRelease(sf::Keyboard::Key key)
{
	/*	switch (key)
		{
		default:
		break;
		}*/
}

void Player::move(float x, float y, float gameTime, TileMapLoader& tileMapLoader)
{
	if (!_isIntersecting)
	{
		_lastPosition = sf::Vector2f(_position.x * _tileSize, _position.y * _tileSize);
	}

	_position.x += x * _movementSpeed * gameTime;
	_position.y += y * _movementSpeed * gameTime;

	_bounds = sf::FloatRect(_position.x * _tileSize, _position.y * _tileSize + _tileSize / 2, (float)_size.x, (float)_size.y / 2);

	static std::vector<sf::FloatRect>* pCollisionObjects = tileMapLoader.getObjects("collision");

	for (unsigned int i = 0; i < pCollisionObjects->size(); i++)
	{
		if (_bounds.intersects((*pCollisionObjects)[i]))
		{
			_isIntersecting = true;
			_position = sf::Vector2f(_lastPosition.x / _tileSize, _lastPosition.y / _tileSize);
			break;
		}
		else
		{
			_isIntersecting = false;
		}
	}

	_character.setPosition(_position.x, _position.y);
}

void Player::handleLiveInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && _state != WALK_DOWN
		&& (_state != WALK_LEFT && _state != WALK_RIGHT))
	{
		_state = WALK_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& (_state != WALK_LEFT && _state != WALK_RIGHT))
	{
		_state = WALK_DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& _state != WALK_RIGHT)
	{
		_state = WALK_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_state = WALK_RIGHT;
	}
	else
	{
		_state = STAY;
	}
}

sf::Vector2f Player::getCurrentPosition()
{
	return sf::Vector2f(_position.x * _tileSize, _position.y * _tileSize);
}
sf::Vector2f Player::getLastPosition()
{
	return _lastPosition;
}

bool Player::intersects(sf::FloatRect bounds)
{
	if (_bounds.intersects(bounds))
		return true;
	else
		return false;
}

bool Player::isMoving()
{
	if (_state == STAY)
	{
		return false;
	}
	else
	{
		return true;
	}
}

short Player::getState()
{
	return _state;
}