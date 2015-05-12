#include "MenuScreen.h"


MenuScreen::MenuScreen(ContentManager* pContentManager, sf::Vector2u screenSize)
	: BaseScreen(pContentManager, screenSize)
{
	std::cout << "MenuScreen" << std::endl;

	_camera.setSize((float)_screenSize.x, (float)_screenSize.y);
	_camera.setCenter(_camera.getSize().x / 2, _camera.getSize().y / 2);
}


MenuScreen::~MenuScreen()
{
	if (_isActivated) delete _btnNewGame;
	if (_isActivated) delete _btnExit;
	if (_isActivated) delete _loadingSprite;
	if (_isActivated) delete _logoSprite;
	if (_isActivated) delete _menuMusic;
	
}

void MenuScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
}

void MenuScreen::handleMouse(sf::Mouse::Button key, bool pressed)
{
	//std::cout << key << "  " << pressed << std::endl;
	_btnNewGame->handleMouse(key, pressed);
	_btnExit->handleMouse(key, pressed);
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------
void MenuScreen::update(float gameTime)
{
	if (_btnNewGame->getState())
	{
		_loadingSprite->setTextureRect(sf::IntRect(0, 0, _screenSize.x, _screenSize.y));
		_screenState = 2;
	}
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------
void MenuScreen::draw(sf::RenderWindow& window)
{
	window.setView(_camera);

	window.draw(*_logoSprite);
	_btnNewGame->draw(window);
	_btnExit->draw(window);
	window.draw(*_loadingSprite);

	if (_btnExit->getState())
	{
		window.close();
	}
}

void MenuScreen::activate()
{
	_pContentManager->loadContent("menuscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_pFonts = _pContentManager->getFonts();
	_screenState = 1;

	sf::Text* text = new sf::Text();
	text->setFont((*_pFonts)["Visitor"]);
	text->setScale(0.5f, 0.5f);
	text->setCharacterSize(28 * 2);
	text->setColor(sf::Color::Black);

	_loadingSprite = new sf::Sprite();
	_loadingSprite->setTexture((*_pTextures)["loading"]);
	_loadingSprite->setTextureRect(sf::IntRect(0, 0, 0, 0));

	_logoSprite = new sf::Sprite();
	_logoSprite->setTexture((*_pTextures)["twb_logo"]);
	_logoSprite->setPosition(0, 40);

	_menuMusic = new sf::Music();
	_menuMusic->openFromFile("Content/Music/song18_0.ogg");
	_menuMusic->setLoop(true);
	_menuMusic->setVolume(60);
	_menuMusic->play();

	// --------------------------------------------------

	text->setString(L"Новая игра");
	_btnNewGame = new ui::Button(337, 190+60, 180, 40, *text);

	text->setString(L"Выход");
	_btnExit = new ui::Button(337, 250+60, 180, 40, *text);

	delete text;

	std::cout << "MenuScreen activated" << std::endl;
	_isActivated = true;
}

void MenuScreen::deactivate()
{
	delete _btnNewGame;
	delete _btnExit;
	delete _loadingSprite;
	delete _logoSprite;
	delete _menuMusic;
	_pContentManager->clear();

	std::cout << "MenuScreen deactivated" << std::endl;
	_isActivated = false;
}

bool MenuScreen::isActivated()
{
	return _isActivated;
}

short MenuScreen::getState()
{
	return _screenState;
}
