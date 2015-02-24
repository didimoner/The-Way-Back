#pragma once
#include <fstream>
#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "AnimatedSprite.h"

class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	void addTexture(std::string file, std::string name);
	void addTexture(std::string file, std::string name, sf::IntRect rect);

	void addSound(std::string file, std::string name);

	void addFont(std::string file, std::string name);

	void loadContent(std::string screenName);

	std::map <std::string, sf::Texture>* getTextures();
	std::map <std::string, sf::SoundBuffer>* getSounds();
	sf::Font* getFont();

	void setRootFolder(std::string folder);
	std::string getRootFolder(void);

	void setTileSize(unsigned short size);
	unsigned short getTileSize();

private:
	std::string _rootDir;
	std::string _imagesDir;
	std::string _fontsDir;
	std::string _soundsDir;

	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::SoundBuffer> _sounds;
	sf::Font _font;

	unsigned short _tileSize;
};
