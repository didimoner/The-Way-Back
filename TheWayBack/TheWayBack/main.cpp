//#include <C:\Program Files (x86)\Visual Leak Detector\include\vld.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"

int main()
{
	Game game(sf::Vector2i(854, 480), "The Way Back", false);
	game.run();

	return 0;
}
