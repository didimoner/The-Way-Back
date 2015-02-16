#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite()
{
	_isPlaying = true;
	_direction = 1;
}

AnimatedSprite::AnimatedSprite(short line, short firstFrame, short lastFrame, float delay,
	short tileSize, RepeatMode repeatMode, bool isLooped)
{
	_line = line - 1;
	_firstFrame = firstFrame - 1;
	_currentFrame = _firstFrame;
	_tempFrame = _currentFrame;
	_lastFrame = lastFrame - 1;
	_delay = delay;
	_tileSize = tileSize;
	_isPlaying = true;
	_isLooped = isLooped;
	_repeatMode = repeatMode;
	_direction = 1;

	setTextureRect(sf::IntRect(_firstFrame * _tileSize, _line * _tileSize, _tileSize, _tileSize));
}

AnimatedSprite::~AnimatedSprite(void)
{
}

void AnimatedSprite::update(float gameTime)
{
	if (!_isPlaying)
	{
		setTextureRect(sf::IntRect(_currentFrame * _tileSize, _line * _tileSize, _tileSize, _tileSize));
		return;
	}

	if (_repeatMode == LOOP)
	{
		if (_tempFrame < _lastFrame + 1)
			_tempFrame += _delay * gameTime;
		else
		{
			if (_isLooped)
			{
				_currentFrame = _firstFrame;
				_tempFrame = _currentFrame;
			}
		}
	}

	if (_repeatMode == ROUND_TRIP)
	{
		if (_direction == 1)
		{
			if (_tempFrame < _lastFrame + 1)
				_tempFrame += _delay * gameTime;
			else
				_direction = -1;
		}
		if (_direction == -1)
		{
			if (_tempFrame > _firstFrame - 1)
				_tempFrame -= _delay * gameTime;
			else
				_direction = 1;
		}
	}

	_currentFrame = (int)_tempFrame;

	if (_currentFrame > _lastFrame)
		_currentFrame = _lastFrame;

	if (_currentFrame < _firstFrame)
		_currentFrame = _firstFrame;
	
	setTextureRect(sf::IntRect(_currentFrame * _tileSize, _line * _tileSize, _tileSize, _tileSize));
}

void AnimatedSprite::setLine(short line)
{
	_line = line - 1;
}
short AnimatedSprite::getLine()
{
	return _line;
}

void AnimatedSprite::setFirstFrame(short frame)
{
	_firstFrame = frame - 1;
	_currentFrame = _firstFrame;
	_tempFrame = _currentFrame;
}
short AnimatedSprite::getFirstFrame()
{
	return _firstFrame;
}

void AnimatedSprite::setLastFrame(short frame)
{
	_lastFrame = frame - 1;
}
short AnimatedSprite::getLastFrame()
{
	return _lastFrame;
}

void AnimatedSprite::setDelay(float delay)
{
	_delay = delay;
}
float AnimatedSprite::getDelay()
{
	return _delay;
}

void AnimatedSprite::setTileSize(short tileSize)
{
	_tileSize = tileSize;
}
short AnimatedSprite::getTileSize()
{
	return _tileSize;
}

void AnimatedSprite::setRepeatMode(RepeatMode repeatMode)
{
	_repeatMode = repeatMode;
}
RepeatMode AnimatedSprite::getRepeatMode()
{
	return _repeatMode;
}

void AnimatedSprite::pause()
{
	_isPlaying = false;
}
void AnimatedSprite::play()
{
	_isPlaying = true;
}
void AnimatedSprite::stop()
{
	_isPlaying = false;
	_currentFrame = _firstFrame;
}

void AnimatedSprite::looped()
{
	_isLooped = true;
}
void AnimatedSprite::linear()
{
	_isLooped = false;
}