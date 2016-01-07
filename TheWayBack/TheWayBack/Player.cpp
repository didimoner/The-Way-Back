#include "Player.h"
#include <iostream>

Player::Player(AnimationManager animationManager, SoundManager soundManager, float speed,
	sf::Vector2f position, sf::Vector2i size, short tileSize, TileMapLoader* pTileMapLoader)
{
	_saveFile = new SaveFileHandler("Content/Saves/save.tws");

	_character = animationManager;
	_sounds = soundManager;
	_movementSpeed = speed / 100;
	_position = position;
	_size = size;
	_state = STAY;
	_tileSize = tileSize;
	_currentAnimation = _character.getCurrentAnimation();
	_character.setPosition(_position.x, _position.y);
	_bounds = sf::FloatRect(_position.x * _tileSize, _position.y * _tileSize, (float)_size.x, (float)_size.y);
	_isIntersecting = false;
	_pTileMapLoader = pTileMapLoader;
}

Player::~Player(void)
{
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void Player::update(float gameTime, sf::View& camera)
{
	handleLiveInput();
	
	switch (_state)
	{
	case STAY:
		_character.stopAnimation(_currentAnimation);
		_character.update(gameTime);
		return;

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

	_character.update(gameTime);
	_currentAnimation = _character.getCurrentAnimation();

	// устанавливаем вьюху и не пускаем ее за границы карты (иначе рисовальщик выйдет за границы массива)
	sf::Vector2f cameraCenter = sf::Vector2f(_character.getPosition().x + _size.x / 2, _character.getPosition().y + _size.y / 2);

	if (_pTileMapLoader->getSize().x < camera.getSize().x)
	{
		cameraCenter.x = camera.getSize().x / 2 - (camera.getSize().x - _pTileMapLoader->getSize().x) / 2;
	}
	else
	{
		if ((cameraCenter.x - camera.getSize().x / 2) < 0)
		{
			cameraCenter.x = camera.getSize().x / 2;
		}

		if ((cameraCenter.x + camera.getSize().x / 2) >= _pTileMapLoader->getSize().x)
		{
			cameraCenter.x = _pTileMapLoader->getSize().x - camera.getSize().x / 2;
		}
		
	}

	if (_pTileMapLoader->getSize().y < camera.getSize().y)
	{
		cameraCenter.y = camera.getSize().y / 2 - (camera.getSize().y - _pTileMapLoader->getSize().y) / 2;
	}
	else
	{
		
		if ((cameraCenter.y - camera.getSize().y / 2) < 0)
		{
			cameraCenter.y = camera.getSize().y / 2;
		}

		if ((cameraCenter.y + camera.getSize().y / 2) >= _pTileMapLoader->getSize().y)
		{
			cameraCenter.y = _pTileMapLoader->getSize().y - camera.getSize().y / 2;
		}
	}

	camera.setCenter(cameraCenter.x, cameraCenter.y);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void Player::draw(sf::RenderWindow& window)
{
	_character.draw(window);
}

// -----------------------------------------------------

void Player::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
	if (pressed)
	{
		switch (key)
		{
		case sf::Keyboard::B:
			_sounds.play("jump");
			break;
		case sf::Keyboard::Space:
			processItemCollision();
			break;

		default:
			break;
		}
	}
	else
	{

	}
	
}

void Player::move(float x, float y, float gameTime)
{
	if (!_isIntersecting)
	{
		_lastPosition = sf::Vector2f(_position.x * _tileSize, _position.y * _tileSize);
	}

	_position.x += x * _movementSpeed * gameTime;
	_position.y += y * _movementSpeed * gameTime;

	_bounds = sf::FloatRect(_position.x * _tileSize, _position.y * _tileSize + _tileSize / 2, (float)_size.x, (float)_size.y / 2);

	processMapCollisions();

	_character.setPosition(_position.x, _position.y);
}

void Player::handleLiveInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && _state != WALK_DOWN
		&& (_state != WALK_LEFT && _state != WALK_RIGHT))
	{
		_state = WALK_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& (_state != WALK_LEFT && _state != WALK_RIGHT))
	{
		_state = WALK_DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& _state != WALK_RIGHT)
	{
		_state = WALK_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_state = WALK_RIGHT;
	}
	else
	{
		_state = STAY;
	}
}

sf::Vector2f Player::getCurrentPosition()
{
	return sf::Vector2f(_position.x * _tileSize, _position.y * _tileSize);
}
sf::Vector2f Player::getLastPosition()
{
	return _lastPosition;
}

bool Player::intersects(sf::FloatRect bounds)
{
	if (_bounds.intersects(bounds))
		return true;
	else
		return false;
}

bool Player::isMoving()
{
	if (_state == STAY)
	{
		return false;
	}
	else
	{
		return true;
	}
}

short Player::getState()
{
	return _state;
}

void Player::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Player::processMapCollisions()
{
	// collision
	for (unsigned int i = 0; i < _pTileMapLoader->getObjects("collision")->size(); i++)
	{
		MapObject currentMapObject = (*_pTileMapLoader->getObjects("collision"))[i];

		if (_bounds.intersects(currentMapObject.rect))
		{
			_isIntersecting = true;
			_position = sf::Vector2f(_lastPosition.x / _tileSize, _lastPosition.y / _tileSize);
			break;
		}
		else
		{
			_isIntersecting = false;
		}
	}

	for (unsigned int i = 0; i < _pTileMapLoader->getObjects("teleport")->size(); i++)
	{
		MapObject currentMapObject = (*_pTileMapLoader->getObjects("teleport"))[i];

		if (_bounds.intersects(currentMapObject.rect))
		{
			_pTileMapLoader->load(currentMapObject.name);
			_position = currentMapObject.initPosition;
			break;
		}
	}
}

void Player::processItemCollision()
{
	// items and containers
	for (unsigned int i = 0; i < _pTileMapLoader->getItems()->size(); i++)
	{
		Item* currItem = &(*_pTileMapLoader->getItems())[i];

		if (!currItem->getState())
			continue;

		if (_bounds.intersects(currItem->getBounds()))
		{
			if (currItem->getDependence()->size() != 0)
			{
				bool flag = true;

				for (unsigned int i = 0; i < currItem->getDependence()->size(); i++)
				{
					if (!_inventory->contains((*currItem->getDependence())[i], 1))
						flag = false;
				}

				if (flag)
				{
					_inventory->add(currItem);
					currItem->setState(false);

					saveItem(currItem);

				}
				else
				{
					std::cout << "You don't have required item!" << std::endl;
				}
			}
			else
			{
				_inventory->add(currItem);
				currItem->setState(false);

				saveItem(currItem);
			}
		}
	}

	for (unsigned int i = 0; i < _pTileMapLoader->getContainers()->size(); i++)
	{
		Container* currConteiner = &(*_pTileMapLoader->getContainers())[i];

		if (!currConteiner->container.getState())
			continue;

		if (_bounds.intersects(currConteiner->container.getBounds()))
		{
			for (unsigned int j = 0; j < currConteiner->items.size(); j++)
			{
				Item* currContainerItem = &currConteiner->items[j];

				if (!currContainerItem->getState())
					continue;

				_inventory->add(currContainerItem);
				currContainerItem->setState(false);

				saveItem(currContainerItem);
			}
		}
	}
}

Inventory* Player::getInventoryPointer()
{
	return _inventory;
}

void Player::initInventory(unsigned short size, float width, float height, std::string header)
{
	_inventory = new Inventory(size, width, height, header);
}

void Player::saveItem(Item* item)
{
	SaveElement parentElement;
	SaveElement childElement;

	parentElement.name = "inventory";

	childElement.name = "item";
	childElement.attrForSearch.first = "id";
	childElement.attrForSearch.second = item->getId();
	childElement.attributes["id"] = item->getId();

	_saveFile->addElement(parentElement, childElement);

	parentElement.attributes.clear();
	childElement.attributes.clear();

	// ----

	parentElement.name = "mapItems";
	childElement.attributes["id"] = item->getId();
	childElement.attributes["state"] = "hidden";

	_saveFile->addElement(parentElement, childElement);
}