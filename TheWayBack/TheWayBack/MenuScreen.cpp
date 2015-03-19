#include "MenuScreen.h"


MenuScreen::MenuScreen(ContentManager* pContentManager)
	: BaseScreen(pContentManager)
{
	std::cout << "MenuScreen" << std::endl;
	_isActivated = false;
	
	_camera.setSize(854, 480);
	_camera.setCenter(_camera.getSize().x / 2, _camera.getSize().y / 2);
}


MenuScreen::~MenuScreen()
{
	if (_isActivated) delete _btnNewGame;
	if (_isActivated) delete _btnExit;
}

void MenuScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
}

void MenuScreen::handleMouse(sf::Keyboard::Key key, bool pressed)
{
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
		_loadingSprite.setTextureRect(sf::IntRect(0, 0, 854, 480));
		_screenState = 2;
	}
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------
void MenuScreen::draw(sf::RenderWindow& window)
{
	window.setView(_camera);

	_btnNewGame->draw(window);
	_btnExit->draw(window);
	window.draw(_loadingSprite);

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

	_loadingSprite.setTexture((*_pTextures)["loading"]);
	_loadingSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));

	// --------------------------------------------------

	text->setString(L"Новая игра");
	_btnNewGame = new ui::Button(337, 190, 180, 40, *text);

	text->setString(L"Выход");
	_btnExit = new ui::Button(337, 250, 180, 40, *text);

	delete text;

	std::cout << "MenuScreen activated" << std::endl;
	_isActivated = true;
}

void MenuScreen::deactivate()
{
	delete _btnNewGame;
	delete _btnExit;
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
