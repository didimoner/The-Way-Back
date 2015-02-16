#include "AnimationManager.h"
#include <iostream>

AnimationManager::AnimationManager()
{
}

AnimationManager::AnimationManager(sf::Texture &texture, short tileSize)
{
	_tileSize = tileSize;
	_animatedSprite.setTexture(texture);
	_animatedSprite.setTileSize(_tileSize);
}

AnimationManager::~AnimationManager(void)
{
	_animations.clear();
}

void AnimationManager::update(float gameTime)
{
	_animations[_currentSprite].update(gameTime);
}

void AnimationManager::draw(sf::RenderWindow& window)
{
	window.draw(_animations[_currentSprite]);
}

void AnimationManager::addAnimation(std::string name, short line, short firstFrame, short lastFrame,
	float delay, RepeatMode repeatMode, bool isLooped)
{
	_animatedSprite.setLine(line);
	_animatedSprite.setFirstFrame(firstFrame);
	_animatedSprite.setLastFrame(lastFrame);
	_animatedSprite.setDelay(delay);
	_animatedSprite.setRepeatMode(repeatMode);
	isLooped ? _animatedSprite.looped() : _animatedSprite.linear();

	_animations[name] = _animatedSprite;
	_currentSprite = name;
}

void AnimationManager::move(float x, float y)
{
	_animations[_currentSprite].move(x, y);
}
void AnimationManager::move(std::string name, float x, float y)
{
	_animations[name].move(x, y);
}

void AnimationManager::setCurrentAnimation(std::string name)
{
	_currentSprite = name;
}
std::string AnimationManager::getCurrentAnimation()
{
	return _currentSprite;
}

void AnimationManager::setPosition(float x, float y)
{
	_animations[_currentSprite].setPosition(x * _tileSize, y * _tileSize);
}
sf::Vector2f AnimationManager::getPosition()
{
	return _animations[_currentSprite].getPosition();
}

void AnimationManager::setPosition(std::string name, float x, float y)
{
	_animations[name].setPosition(x * _tileSize, y * _tileSize);
}
sf::Vector2f AnimationManager::getPosition(std::string name)
{
	return _animations[name].getPosition();
}

void AnimationManager::pauseAnimation(std::string name)
{
	_animations[name].pause();
}
void AnimationManager::playAnimation(std::string name)
{
	_animations[name].play();
}
void AnimationManager::stopAnimation(std::string name)
{
	_animations[name].stop();
}