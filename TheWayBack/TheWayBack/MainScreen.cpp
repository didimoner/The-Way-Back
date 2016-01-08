#include "MainScreen.h"
#include <iostream>

MainScreen::MainScreen(sf::Vector2u screenSize)
	: BaseScreen(screenSize)
{
	std::cout << "MainScreen" << std::endl;
}

MainScreen::~MainScreen()
{
	if (_isActivated) delete _player;
	if (_isActivated) delete _tileMapLoader;
	if (_isActivated) delete _pInventory;

	_animationManagers.clear();
	_spriteManagers.clear();
	_soundManagers.clear();
	_uiObjects.clear();
}

void MainScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
	_player->handleKeyboard(key, pressed);

	for (unsigned int i = 0; i < _uiObjects.size(); i++)
	{
		_uiObjects[i]->handleKeyboard(key, pressed);
	}
}

void MainScreen::handleMouse(sf::Keyboard::Key key, bool pressed)
{
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void MainScreen::update(float gameTime)
{
	_player->update(gameTime, _camera);

	for (unsigned int i = 0; i < _uiObjects.size(); i++)
	{
		_uiObjects[i]->update(gameTime);
	}
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void MainScreen::draw(sf::RenderWindow& window)
{
	window.setView(_camera);

	_tileMapLoader->draw(window, _entities, _camera);

	for (unsigned int i = 0; i < _uiObjects.size(); i++)
	{
		_uiObjects[i]->setPosition(_camera.getCenter().x, _camera.getCenter().y);
		_uiObjects[i]->draw(window);
	}
}

void MainScreen::activate()
{
	_contentManager.loadContent("mainscreen");
	_pTextures = _contentManager.getTextures();
	_pSounds = _contentManager.getSounds();
	_pFonts = _contentManager.getFonts();
	_screenState = 2;

	// загружаем сохранения

	SaveFileHandler saveFile("Content/Saves/save.tws");
	std::string::size_type sz;
	std::pair<std::string, std::string> search;

	// ------

	AnimationManager playerOne((*_pTextures)["char1"], _tileSize);
	playerOne.addAnimation("walk_down", 1, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_up", 4, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_left", 2, 1, 3, 0.004f, LOOP, true);
	playerOne.addAnimation("walk_right", 3, 1, 3, 0.004f, LOOP, true);

	SoundManager* pPlayerSounds;
	pPlayerSounds = new SoundManager();
	pPlayerSounds->addSound((*_pSounds)["collect"], "jump");

	_tileMapLoader = new TileMapLoader("Content/Maps", 2, _pTextures);

	// загружаем текущую карту из сохранений
	std::string currentMap = saveFile.getElement("currentMap", "", search, "name");
	if (currentMap != "")
	{
		_tileMapLoader->load(currentMap);
	}
	else
	{
		_tileMapLoader->load("world_1");
	}

	// загружаем текущие координаты персонажа из сохранений
	sf::Vector2f playerPosition;

	std::string x = saveFile.getElement("playerPosition", "", search, "x");
	std::string y = saveFile.getElement("playerPosition", "", search, "y");

	if (x != "" && y != "")
	{
		playerPosition = sf::Vector2f(stof(x, &sz), stof(y, &sz));
	}
	else
	{
		playerPosition = sf::Vector2f(47, 26);
	}

	sf::Vector2f cameraCenter = sf::Vector2f(playerPosition.x * 32 + 16, playerPosition.y * 32 + 16);

	// ------

	_player = new Player(playerOne, *(pPlayerSounds), 0.24f, playerPosition,
		sf::Vector2i(32, 32), _tileSize, _tileMapLoader);
	_entities.push_back(_player);

	delete pPlayerSounds;

	// выставляем камеру по координатам персонажа
	_camera.setSize((float)_screenSize.x, (float)_screenSize.y);
	_cameraSpeed = sf::Vector2f(0.2f, 0.18f);

	unsigned short tileW = _tileMapLoader->getCurrentMap().tileWidth;
	unsigned short tileH = _tileMapLoader->getCurrentMap().tileHeight;

	if ((_tileMapLoader->getSize().x - playerPosition.x * tileW + _tileSize / 2) < (float)_screenSize.x / 2)
	{
		cameraCenter.x -= _screenSize.x / 2 - (_tileMapLoader->getSize().x - playerPosition.x * tileW - _tileSize / 2);
	}
	if ((_tileMapLoader->getSize().y - playerPosition.y * tileH + _tileSize / 2) < (float)_screenSize.y / 2)
	{
		cameraCenter.y -= _screenSize.y / 2 - (_tileMapLoader->getSize().y - playerPosition.y * tileH - _tileSize / 2);
	}

	if ((playerPosition.x * tileW + _tileSize / 2) < (float)_screenSize.x / 2)
	{
		cameraCenter.x += _screenSize.x / 2 - (playerPosition.x * tileW + _tileSize / 2);
	}
	if ((playerPosition.y * tileH + _tileSize / 2) < (float)_screenSize.y / 2)
	{
		cameraCenter.y += _screenSize.y / 2 - (playerPosition.y * tileH + _tileSize / 2);
	}

	_camera.setCenter(cameraCenter);
	std::cout << "MainScreen activated" << std::endl;
	_isActivated = true;

	// ----------------------------------------------------
	_player->initInventory(16, 480, 360, "Invertory", _tileMapLoader);
	_pInventory = _player->getInventoryPointer();
	_uiObjects.push_back(_pInventory);
}

void MainScreen::deactivate()
{
	SaveFileHandler saveFile("Content/Saves/save.tws");
	std::pair<std::string, std::string> search;
	search.first = "";
	search.second = "";

	// сохраняем текущие координаты
	saveFile.deleteElement("playerPosition", "", search);

	SaveElement parentElement;
	SaveElement childElement;
	childElement.name = "";

	parentElement.name = "playerPosition";
	parentElement.attributes["x"] = std::to_string(_player->getCurrentPosition().x / _tileMapLoader->getCurrentMap().tileWidth);
	parentElement.attributes["y"] = std::to_string(_player->getCurrentPosition().y / _tileMapLoader->getCurrentMap().tileWidth);

	saveFile.addElement(parentElement, childElement);

	parentElement.attributes.clear();
	childElement.attributes.clear();

	// сохраняем текущую карту
	saveFile.deleteElement("currentMap", "", search);

	parentElement.name = "currentMap";
	parentElement.attributes["name"] = _tileMapLoader->getCurrentMap().name;

	saveFile.addElement(parentElement, childElement);
	
	// -------------------

	delete _tileMapLoader;
	delete _player;
	delete _pInventory;
	_entities.clear();
	_contentManager.clear();
	_uiObjects.clear();

	std::cout << "MainScreen deactivated" << std::endl;
	_isActivated = false;
}

bool MainScreen::isActivated()
{
	return _isActivated;
}