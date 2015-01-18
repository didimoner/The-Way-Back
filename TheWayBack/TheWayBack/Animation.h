#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"

class Animation :
	public sf::Sprite
{
public:
	Animation();
	Animation(short rows, short firstFrame, short lastFrame, 
		float delay, sf::Vector2i tileSize, bool isRoundUp, bool isLooped);
	~Animation();

	void update(float gameTime);

	void setRows(short rows);
	short getRows();

	void setFirstFrame(short frame);
	short getFirstFrame();

	void setLastFrame(short frame);
	short getLastFrame();

	void setDelay(float delay);
	float getDelay();

	void setTileSize(sf::Vector2i tileSize);
	sf::Vector2i getTileSize();

	void setRepeatMode(bool isRoundUp);
	bool getRepeatMode();

	void looped();
	void linear();

	void pause();
	void play();

private:
	short _rows;
	short _currentRow;
	short _firstFrame;
	short _currentFrame;
	float _tempFrame;
	short _lastFrame;
	float _delay;
	sf::Vector2i _tileSize;
	bool _isPlaying;
	bool _isRoundUp;
	bool _isLooped;
	short _direction;
};

