#include "SplashScreen.h"


SplashScreen::SplashScreen(ContentManager* pContentManager)
	: BaseScreen(pContentManager)
{
	std::cout << "SplashScreen" << std::endl;
	_isActivated = false;
}


SplashScreen::~SplashScreen()
{
	if (_isActivated) delete _animation;
}

void SplashScreen::handleKeyPress(sf::Keyboard::Key key, bool isPressed)
{

}

// -----------------------------------------------------
// UPDATE FUNCTION--------------------------------------
// -----------------------------------------------------

void SplashScreen::update(float gameTime)
{
	_animation->update(gameTime);
}

// -----------------------------------------------------
// DRAW FUNCTION----------------------------------------
// -----------------------------------------------------

void SplashScreen::draw(sf::RenderWindow& window)
{
	window.draw(*_animation);
}


void SplashScreen::activate()
{

	_pContentManager->loadContent("splashscreen");
	_pTextures = _pContentManager->getTextures();
	_pSounds = _pContentManager->getSounds();
	_screenState = 0;

	_animation = new Animation(6, 1, 5, 0.02f, sf::Vector2i(192, 192), false, true);
	_animation->setTexture((*_pTextures)["loading32322"]);
	_animation->setPosition(sf::Vector2f((float)8 * _tileSize, (float)4 * _tileSize));

	std::cout << "SplashScreen activated" << std::endl;
	_isActivated = true;
}

void SplashScreen::deactivate()
{
	delete _animation;
	_pContentManager->clear();

	std::cout << "SplashScreen deactivated" << std::endl;
	_isActivated = false;
}

bool SplashScreen::isActivated()
{
	return _isActivated;
}