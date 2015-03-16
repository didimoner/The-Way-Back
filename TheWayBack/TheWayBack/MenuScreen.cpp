#include "MenuScreen.h"


MenuScreen::MenuScreen(ContentManager* contentManager)
	: BaseScreen(contentManager)
{
	std::cout << "MenuScreen" << std::endl;
	_isActivated = false;
	
	_camera.setSize(854, 480);
	_camera.setCenter(_camera.getSize().x / 2, _camera.getSize().y / 2);
}


MenuScreen::~MenuScreen()
{
	if (_isActivated) delete _animation;
}

void MenuScreen::handleKeyboard(sf::Keyboard::Key key, bool pressed)
{
	std::cout << "Button state: " << _button->getState() << std::endl;
}

void MenuScreen::handleMouse(sf::Keyboard::Key key, bool pressed)
{
	_button->handleMouse(key, pressed);

}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void MenuScreen::update(float gameTime)
{
	_animation->update(gameTime);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void MenuScreen::draw(sf::RenderWindow& window)
{
	window.setView(_camera);
	window.draw(*_animation);
	_button->draw(window);
}


void MenuScreen::activate()
{
	_pContentManager->loadContent("menuscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_pFonts = _pContentManager->getFonts();

	_animation = new Animation(6, 1, 5, 0.015f, sf::Vector2i(192, 192), false, true);
	_animation->setTexture((*_pTextures)["ffloadding"]);
	_animation->setPosition(sf::Vector2f((float)2 * _tileSize, (float)7 * _tileSize));

	sf::Text* text = new sf::Text();
	text->setFont((*_pFonts)["Visitor"]);
	text->setScale(0.5f, 0.5f);
	text->setCharacterSize(28 * 2);
	text->setString(L"Новая игра");
	text->setColor(sf::Color::Black);

	_button = new ui::Button(120, 40, 180, 40, *text);
	delete text;

	std::cout << "MenuScreen activated" << std::endl;
	_isActivated = true;
}

void MenuScreen::deactivate()
{
	delete _animation;
	delete _button;
	_pContentManager->clear();

	std::cout << "MenuScreen deactivated" << std::endl;
	_isActivated = false;
}

bool MenuScreen::getState()
{
	return _isActivated;
}