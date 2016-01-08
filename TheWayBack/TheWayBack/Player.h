#pragma once
#include "entity.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "TileMapLoader.h"
#include "Inventory.h"
#include "SaveFileHandler.h"

class Player :
	public Entity
{
public:
	Player(AnimationManager animationManager, SoundManager soundManager,
		float speed, sf::Vector2f position, sf::Vector2i size, short tileSize, TileMapLoader* pTileMapLoader);
	~Player(void);

	virtual void update(float gameTime, sf::View& camera);
	virtual void draw(sf::RenderWindow& window);

	void handleKeyboard(sf::Keyboard::Key key, bool pressed);

	void move(float x, float y, float gameTimer);

	bool intersects(sf::FloatRect bounds);

	short getState();
	Inventory* getInventoryPointer();

	sf::Vector2f getCurrentPosition();
	sf::Vector2f getLastPosition();

	void setPosition(sf::Vector2f position);
	void initInventory(unsigned short size, float width, float height, std::string header);

	bool isMoving();

private:
	void handleLiveInput();
	void processMapCollisions();
	void processItemCollision();
	void saveItem(Item* item);
	void cameraCheck(sf::View& camera);

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
	SaveFileHandler* _saveFile;
	TileMapLoader* _pTileMapLoader;
};
