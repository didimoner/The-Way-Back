#include "MainScreen.h"
#include <iostream>

MainScreen::MainScreen(ContentManager* contentManager)
	: BaseScreen(contentManager)
{
	AnimationManager playerOne((*_pTextures)["char1"], _pContentManager->getTileSize());
	playerOne.addAnimation("walk_down", 1, 1, 3, 0.003f, LOOP, true);
	playerOne.addAnimation("walk_up", 4, 1, 3, 0.003f, LOOP, true);
	playerOne.addAnimation("walk_left", 2, 1, 3, 0.003f, LOOP, true);
	playerOne.addAnimation("walk_right", 3, 1, 3, 0.003f, LOOP, true);

	/*_animManager = new AnimationManager((*_pTextures)["loading2"], 192);
	_animManager->addAnimation("loading", 6, 1, 5, 0.008f, LOOP, SINGLE, true);*/

	SoundManager playerSounds;
	playerSounds.addSound((*_pSounds)["collect"], "jump");

	_player = new Player(playerOne, playerSounds, 0.004f, sf::Vector2f(0, 0), sf::Vector2i(32, 32), _tileSize);

	_animation = new Animation(6, 1, 5, 0.01f, sf::Vector2i(192, 192), true, true);
	_animation->setTexture((*_pTextures)["loading"]);
	_animation->setPosition(sf::Vector2f((float)7 * _tileSize, (float)7 * _tileSize));

	/*SpriteManager spriteOne((*_pTextures)["char4"], _pContentManager->getTileSize());
	spriteOne.addSprite("look_down", sf::Vector2f(1, 0), sf::Vector2i(0, 0));
	spriteOne.addSprite("look_up", sf::Vector2f(1, 1), sf::Vector2i(0, 3));
	spriteOne.addSprite("look_left", sf::Vector2f(1, 2), sf::Vector2i(0, 1));
	spriteOne.addSprite("look_right", sf::Vector2f(1, 3), sf::Vector2i(0, 2));
	_spriteManagers["justSprite"] = spriteOne;*/

	TileMapLoader tileMap;
	tileMap.setMapsDir("Content/Maps");
	tileMap.load("map.tmx");
}

MainScreen::~MainScreen()
{
	delete _player;
	delete _animation;
}

void MainScreen::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
{
	isPressed ? _player->handleKeyPress(key) : _player->handleKeyRelease(key);
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void MainScreen::update(float gameTime)
{
	/*for each(std::pair<std::string, AnimationManager> items in _animationManagers)
	{
	_animationManagers[items.first].update(gameTime);
	}*/
	//std::cout << _player->getPosition().x << " : " << _player->getPosition().y << std::endl;
	_player->update(gameTime);
	_animation->update(gameTime);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void MainScreen::draw(sf::RenderWindow &window)
{
	/*for each(std::pair<std::string, AnimationManager> items in _animationManagers)
	{
	_animationManagers[items.first].draw(window);
	}

	for each(std::pair<std::string, SpriteManager> items in _spriteManagers)
	{
	_spriteManagers[items.first].draw(window);
	}*/

	_player->draw(window);
	window.draw(*_animation);
}