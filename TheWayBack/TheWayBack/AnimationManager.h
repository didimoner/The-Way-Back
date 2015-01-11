#pragma once
#include "SFML\Graphics.hpp"

#include "AnimatedSprite.h"
#include "ContentManager.h"

class AnimationManager
{
public:
	AnimationManager();
	AnimationManager(sf::Texture &texture, short tileSize);
	~AnimationManager();

	void update(float gameTime);
	void draw(sf::RenderWindow& window);

	void addAnimation(std::string name, short line, short firstFrame, short lastFrame,
		float delay, RepeatMode repeatMode, bool isLooped);

	void setCurrentAnimation(std::string name);
	std::string getCurrentAnimation();

	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setPosition(std::string name, float x, float y);
	sf::Vector2f getPosition(std::string name);

	void setOffset(std::string name, float x, float y);

	void pauseAnimation(std::string name);
	void playAnimation(std::string name);

private:
	AnimatedSprite _animatedSprite;
	std::map <std::string, AnimatedSprite> _animations;
	std::string _currentSprite;
	short _tileSize;
};
