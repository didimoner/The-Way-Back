#pragma once
#include "entity.h"
#include "AnimationManager.h"
#include "SoundManager.h"

class Player :
	public Entity
{
public:
	Player(AnimationManager animationManager, SoundManager soundManager,
		float speed, sf::Vector2f position, sf::Vector2i size, short tileSize);
	~Player(void);

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	void handleKeyPress(sf::Keyboard::Key key);
	void handleKeyRelease(sf::Keyboard::Key key);

	void move(float x, float y, float gameTime);

	bool intersects(sf::FloatRect bounds);

	sf::Vector2f getPosition();

private:
	void handleLiveInput();

	AnimationManager _character;
	SoundManager _sounds;
	std::string _currentAnimation;
	float _movementSpeed;
	bool _isAlive;
	enum { STAY, WALK_UP, WALK_DOWN, WALK_LEFT, WALK_RIGHT } _state;
	short _tileSize;
};
