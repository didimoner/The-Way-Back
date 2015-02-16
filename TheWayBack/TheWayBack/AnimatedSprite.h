#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"

enum RepeatMode
{
	LOOP = 0,
	ROUND_TRIP = 1
};

class AnimatedSprite :
	public sf::Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(short line, short firstFrame, short lastFrame, float delay, 
		short tileSize, RepeatMode repeatMode, bool isLooped);
	~AnimatedSprite();

	void update(float gameTime);

	void setLine(short line);
	short getLine();

	void setFirstFrame(short frame);
	short getFirstFrame();

	void setLastFrame(short frame);
	short getLastFrame();

	void setDelay(float delay);
	float getDelay();

	void setTileSize(short tileSize);
	short getTileSize();

	void setRepeatMode(RepeatMode repeatMode);
	RepeatMode getRepeatMode();

	void looped();
	void linear();

	void pause();
	void play();
	void stop();

private:
	short _line;
	short _firstFrame;
	short _currentFrame;
	float _tempFrame;
	short _lastFrame;
	float _delay;
	short _tileSize;
	bool _isPlaying;
	RepeatMode _repeatMode;
	bool _isLooped;
	short _direction;
};
