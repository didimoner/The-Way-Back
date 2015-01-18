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
	_bounds = sf::FloatRect(_position.x, _position.y, (float)_size.x, (float)_size.y);
}

Player::~Player(void)
{
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void Player::update(float gameTime)
{
	handleLiveInput();

	switch (_state)
	{
	case STAY:
		_character.pauseAnimation(_currentAnimation);
		break;

	case WALK_UP:
		_character.setCurrentAnimation("walk_up");
		_character.playAnimation(_currentAnimation);
		move(0, -1, gameTime);
		break;

	case WALK_DOWN:
		_character.setCurrentAnimation("walk_down");
		_character.playAnimation(_currentAnimation);
		move(0, 1, gameTime);
		break;

	case WALK_LEFT:
		_character.setCurrentAnimation("walk_left");
		_character.playAnimation(_currentAnimation);
		move(-1, 0, gameTime);
		break;

	case WALK_RIGHT:
		_character.setCurrentAnimation("walk_right");
		_character.playAnimation(_currentAnimation);
		move(1, 0, gameTime);
		break;

	default:
		_character.pauseAnimation(_currentAnimation);
		break;
	}

	_currentAnimation = _character.getCurrentAnimation();
	_character.setPosition(_position.x * _tileSize, _position.y * _tileSize);
	_bounds = sf::FloatRect(_position.x * _tileSize, _position.y * _tileSize, (float)_size.x, (float)_size.y);
	_character.update(gameTime);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void Player::draw(sf::RenderWindow &window)
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

void Player::move(float x, float y, float gameTime)
{
	_position.x += x * _movementSpeed * gameTime;
	_position.y += y * _movementSpeed * gameTime;
}

void Player::handleLiveInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _state != WALK_DOWN
		&& (_state != WALK_LEFT && _state != WALK_RIGHT))
	{
		_state = WALK_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& (_state != WALK_LEFT && _state != WALK_RIGHT))
	{
		_state = WALK_DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& _state != WALK_RIGHT)
	{
		_state = WALK_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_state = WALK_RIGHT;
	}
	else
	{
		_state = STAY;
	}
}

sf::Vector2f Player::getPosition()
{
	return _character.getPosition();
}

bool Player::intersects(sf::FloatRect bounds)
{
	if (_bounds.intersects(bounds))
		return true;
	else
		return false;
}