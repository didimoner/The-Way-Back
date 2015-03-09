#include "MainScreen.h"
#include <iostream>

MainScreen::MainScreen(ContentManager* contentManager)
	: BaseScreen(contentManager)
{
	std::cout << "MainScreen" << std::endl;
	_isActivated = false;
}

MainScreen::~MainScreen()
{
	if (_isActivated) delete _player;
	if (_isActivated) delete _tileMapLoader;
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

void MainScreen::activate()
{
	_pContentManager->loadContent("mainscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_pFont = _pContentManager->getFont();

	_camera.setSize(854, 480);
	_camera.setCenter(_camera.getSize().x / 2, _camera.getSize().y / 2);
	_cameraSpeed = sf::Vector2f(0.2f, 0.18f);

	AnimationManager playerOne((*_pTextures)["char1"], _tileSize);
	playerOne.addAnimation("walk_down", 1, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_up", 4, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_left", 2, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_right", 3, 1, 3, 0.004f, LOOP, true);

	SoundManager* pPlayerSounds;
	pPlayerSounds = new SoundManager();
	pPlayerSounds->addSound((*_pSounds)["collect"], "jump");

	_tileMapLoader = new TileMapLoader("Content/Maps", 2);
	_tileMapLoader->load("bigmap_notready.tmx", _pTextures);

	_player = new Player(playerOne, *(pPlayerSounds), 0.24f, sf::Vector2f(1, 2),
		sf::Vector2i(32, 32), _tileSize);
	_entities.push_back(_player);

	delete pPlayerSounds;

	std::cout << "MainScreen activated" << std::endl;
	_isActivated = true;
}

void MainScreen::deactivate()
{
	//delete _tileMapLoader;

	delete _player;
	_entities.clear();
	_pContentManager->clear();
	_tileMapLoader->clear();

	std::cout << "MainScreen deactivated" << std::endl;
	_isActivated = false;
}

bool MainScreen::getState()
{
	return _isActivated;
}