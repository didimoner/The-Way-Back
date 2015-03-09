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

void MenuScreen::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
{
	
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
}


void MenuScreen::activate()
{
	_pContentManager->loadContent("menuscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();

	_animation = new Animation(6, 1, 5, 0.015f, sf::Vector2i(192, 192), false, true);
	_animation->setTexture((*_pTextures)["ffloadding"]);
	_animation->setPosition(sf::Vector2f((float)2 * _tileSize, (float)7 * _tileSize));

	std::cout << "MenuScreen activated" << std::endl;
	_isActivated = true;
}

void MenuScreen::deactivate()
{
	delete _animation;
	_pContentManager->clear();

	std::cout << "MenuScreen deactivated" << std::endl;
	_isActivated = false;
}

bool MenuScreen::getState()
{
	return _isActivated;
}