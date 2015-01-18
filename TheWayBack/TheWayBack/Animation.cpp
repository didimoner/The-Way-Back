#include "Animation.h"
#include <iostream>

Animation::Animation()
{
}
Animation::Animation(short rows, short firstFrame, short lastFrame, 
	float delay, sf::Vector2i tileSize, bool isRoundUp, bool isLooped)
{
	_rows = rows;
	_currentRow = 0;
	_firstFrame = firstFrame - 1;
	_currentFrame = _firstFrame;
	_tempFrame = _currentFrame;
	_lastFrame = lastFrame - 1;
	_delay = delay;
	_tileSize = tileSize;
	_isPlaying = true;
	_isLooped = isLooped;
	_isRoundUp = isRoundUp;
	_direction = 1;
}
Animation::~Animation()
{
}

void Animation::update(float gameTime)
{
	if (!_isPlaying)
		return;

	if (!_isRoundUp)
	{
		if (_tempFrame < _lastFrame + 1)
			_tempFrame += _delay * gameTime;
		else
		{
			if (_isLooped)
			{
				_currentFrame = _firstFrame;
				_tempFrame = _currentFrame;

				if (_currentRow < _rows)
					_currentRow++;
				else
					_currentRow = 0;
			}
		}
	}
	else
	{
		if (_direction == 1)
		{
			if (_tempFrame < _lastFrame + 1)
				_tempFrame += _delay * gameTime;
			else
			{
				if (_currentRow >= _rows - 1)
					_direction = -1;
				else
				{
					_currentRow++;
					_tempFrame = _firstFrame;
				}
			}
		}
		if (_direction == -1)
		{
			if (_tempFrame > _firstFrame)
				_tempFrame -= _delay * gameTime;
			else
			{
				if (_currentRow <= 0)
					_direction = 1;
				else
				{
					_currentRow--;
					_tempFrame = _lastFrame + 1;
				}
					
			}
		}

	}

	_currentFrame = (int)_tempFrame;

	if (_currentFrame > _lastFrame)
		_currentFrame = _lastFrame;

	std::cout << "Current frame and line: " << _currentFrame << " " << _currentRow << std::endl;

	if (_currentFrame < _firstFrame)
		_currentFrame = _firstFrame;

	setTextureRect(sf::IntRect(_currentFrame * _tileSize.x, _currentRow * _tileSize.y, _tileSize.x, _tileSize.y));
}

void Animation::setRows(short rows)
{
	_rows = rows - 1;
}
short Animation::getRows()
{
	return _rows;
}

void Animation::setFirstFrame(short frame)
{
	_firstFrame = frame - 1;
	_currentFrame = _firstFrame;
	_tempFrame = _currentFrame;
}
short Animation::getFirstFrame()
{
	return _firstFrame;
}

void Animation::setLastFrame(short frame)
{
	_lastFrame = frame - 1;
}
short Animation::getLastFrame()
{
	return _lastFrame;
}

void Animation::setDelay(float delay)
{
	_delay = delay;
}
float Animation::getDelay()
{
	return _delay;
}

void Animation::setTileSize(sf::Vector2i tileSize)
{
	_tileSize = tileSize;
}
sf::Vector2i Animation::getTileSize()
{
	return _tileSize;
}

void Animation::setRepeatMode(bool isRoundUp)
{
	_isRoundUp = isRoundUp;
}
bool Animation::getRepeatMode()
{
	return _isRoundUp;
}

void Animation::pause()
{
	_isPlaying = false;
}
void Animation::play()
{
	_isPlaying = true;
}

void Animation::looped()
{
	_isLooped = true;
}
void Animation::linear()
{
	_isLooped = false;
}