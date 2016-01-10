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
	std::map <std::string, sf::Font>* getFonts();

	void setRootFolder(std::string folder);
	std::string getRootFolder(void);

	void setTileSize(unsigned short size);
	unsigned short getTileSize();

	void clear();

private:
	std::string _rootDir;
	std::string _imagesDir;
	std::string _fontsDir;
	std::string _soundsDir;
	std::string _resourcesDir;

	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::SoundBuffer> _sounds;
	std::map<std::string, sf::Font> _fonts;

	unsigned short _tileSize;
};
