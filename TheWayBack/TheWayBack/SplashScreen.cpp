#include "SplashScreen.h"


SplashScreen::SplashScreen(sf::Vector2u screenSize)
	: BaseScreen(screenSize)
{
	std::cout << "SplashScreen" << std::endl;
	_splashDuration = 4.f;

	_camera.setSize((float)_screenSize.x, (float)_screenSize.y);
	_camera.setCenter(_camera.getSize().x / 2, _camera.getSize().y / 2);
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
{
}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------
void SplashScreen::update(float gameTime)
{
	if (_clock.getElapsedTime().asSeconds() >= _splashDuration - 1)
	{
		_blackRectTransperency += 8;
		if (_blackRectTransperency >= 255)
		{
			_blackRectTransperency = 255;
			_screenState = 1;
		}
	}

	if (_blackRectTransperency > 0)
	{
		_blackRectTransperency -= 3;
	}

	_blackRect.setFillColor(sf::Color::Color(0, 0, 0, (sf::Uint8)_blackRectTransperency));
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------
void SplashScreen::draw(sf::RenderWindow& window)
{
	window.setView(_camera);

	window.draw(_splashSprite);
	window.draw(_blackRect);
}

void SplashScreen::activate()
{
	_contentManager.loadContent("splashscreen");
	_pTextures = _contentManager.getTextures();
	_pSounds = _contentManager.getSounds();
	_screenState = 0;
	_blackRectTransperency = 255;

	_splashSprite.setTexture((*_pTextures)["splash"]);
	_splashSprite.setTextureRect(sf::IntRect(0, 0, _screenSize.x, _screenSize.y));

	_blackRect.setSize(sf::Vector2f((float)_screenSize.x, (float)_screenSize.y));

	std::cout << "SplashScreen activated" << std::endl;
	_isActivated = true;
}

void SplashScreen::deactivate()
{
	_contentManager.clear();

	std::cout << "SplashScreen deactivated" << std::endl;
	_isActivated = false;
}

bool SplashScreen::isActivated()
{
	return _isActivated;
}

short SplashScreen::getState()
{
	return _screenState;
}
