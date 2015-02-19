#include "MainScreen.h"
#include <iostream>

MainScreen::MainScreen(ContentManager* contentManager)
	: BaseScreen(contentManager)
{
	
	_camera.setSize(854, 480);
	_camera.setCenter(_camera.getSize().x / 2, _camera.getSize().y / 2);
	_cameraSpeed = sf::Vector2f(0.2f, 0.18f);

	AnimationManager playerOne((*_pTextures)["char1"], _pContentManager->getTileSize());
	playerOne.addAnimation("walk_down", 1, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_up", 4, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_left", 2, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_right", 3, 1, 3, 0.004f, LOOP, true);

	SoundManager playerSounds;
	playerSounds.addSound((*_pSounds)["collect"], "jump");

	_player = new Player(playerOne, playerSounds, 0.24f, sf::Vector2f(1, 2),
		sf::Vector2i(32, 32), _tileSize);
	_entities.push_back(_player);

	_tileMapLoader = new TileMapLoader("Content/Maps", 2);
	_tileMapLoader->load("bigmap_notready.tmx", _pTextures);

	//_animation = new Animation(6, 1, 5, 0.009f, sf::Vector2i(192, 192), false, true);
	//_animation->setTexture((* _pTextures)["loading2"]);
	//_animation->setPosition(sf::Vector2f((float)7 * _tileSize, (float)7 * _tileSize));
}

MainScreen::~MainScreen()
{
	delete _player;
	delete _animation;
	delete _tileMapLoader;
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
	_player->update(gameTime, _camera, *_tileMapLoader);
	//_animation->update(gameTime);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void MainScreen::draw(sf::RenderWindow& window)
{
	_tileMapLoader->draw(window, _entities, _camera);
	//_player->draw(window);
	window.setView(_camera);
	//window.draw(* _animation);
}