#pragma once
#include "entity.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "TileMapLoader.h"
#include "Inventory.h"

class Player :
	public Entity
{
public:
	Player(AnimationManager animationManager, SoundManager soundManager,
		float speed, sf::Vector2f position, sf::Vector2i size, short tileSize);
	~Player(void);

	virtual void update(float gameTime, sf::View& camera, TileMapLoader* tileMapLoader);
	virtual void draw(sf::RenderWindow& window);

	void handleKeyboard(sf::Keyboard::Key key, bool pressed);

	void move(float x, float y, float gameTime, TileMapLoader* tileMapLoader);

	bool intersects(sf::FloatRect bounds);

	short getState();

	sf::Vector2f getCurrentPosition();
	sf::Vector2f getLastPosition();

	bool isMoving();

private:
	void handleLiveInput();

	AnimationManager _character;
	SoundManager _sounds;
	std::string _currentAnimation;
	float _movementSpeed;
	bool _isAlive;
	enum { STAY, WALK_UP, WALK_DOWN, WALK_LEFT, WALK_RIGHT } _state;
	short _tileSize;
	sf::Vector2f _lastPosition;
	sf::Vector2f _cameraMovementSpeed;
	bool _isIntersecting;
	Inventory* _inventory;
};
