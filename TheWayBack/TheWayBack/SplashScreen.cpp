#include "SplashScreen.h"


SplashScreen::SplashScreen(ContentManager* pContentManager)
	: BaseScreen(pContentManager)
{
	std::cout << "SplashScreen" << std::endl;
	_isActivated = false;
	_splashDuration = 4.f;
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
	window.draw(_splashSprite);
	window.draw(_blackRect);
}

void SplashScreen::activate()
{
	_pContentManager->loadContent("splashscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_screenState = 0;
	_blackRectTransperency = 255;

	_splashSprite.setTexture((*_pTextures)["splash"]);
	_blackRect.setSize(sf::Vector2f(854, 480));
	std::cout << "SplashScreen activated" << std::endl;
	_isActivated = true;
}

void SplashScreen::deactivate()
{
	_pContentManager->clear();

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
