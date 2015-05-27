#include "MainScreen.h"
#include <iostream>

MainScreen::MainScreen(ContentManager* contentManager, sf::Vector2u screenSize)
	: BaseScreen(contentManager, screenSize)
{
	std::cout << "MainScreen" << std::endl;
}

MainScreen::~MainScreen()
{
	if (_isActivated) delete _player;
	if (_isActivated) delete _tileMapLoader;

	_animationManagers.clear();
	_spriteManagers.clear();
	_soundManagers.clear();
}

void MainScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
	_player->handleKeyboard(key, pressed);
}

void MainScreen::handleMouse(sf::Keyboard::Key key, bool pressed)
{
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void MainScreen::update(float gameTime)
{
	_player->update(gameTime, _camera, _tileMapLoader);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void MainScreen::draw(sf::RenderWindow& window)
{
	_tileMapLoader->draw(window, _entities, _camera);
	window.setView(_camera);
}

void MainScreen::activate()
{
	_pContentManager->loadContent("mainscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_pFonts = _pContentManager->getFonts();
	_screenState = 2;

	_camera.setSize((float)_screenSize.x, (float)_screenSize.y);
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

	_tileMapLoader = new TileMapLoader("Content/Maps", 2, _pTextures);
	_tileMapLoader->load("bigmap_notready");

	_player = new Player(playerOne, *(pPlayerSounds), 0.24f, sf::Vector2f(1, 2),
		sf::Vector2i(32, 32), _tileSize);
	_entities.push_back(_player);

	delete pPlayerSounds;

	std::cout << "MainScreen activated" << std::endl;
	_isActivated = true;
}

void MainScreen::deactivate()
{
	delete _tileMapLoader;
	delete _player;
	_entities.clear();
	_pContentManager->clear();

	std::cout << "MainScreen deactivated" << std::endl;
	_isActivated = false;
}

bool MainScreen::isActivated()
{
	return _isActivated;
}