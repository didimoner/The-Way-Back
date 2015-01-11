#pragma once
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

	void loadContent(void);

	std::map <std::string, sf::Texture>* getTextures();
	std::map <std::string, sf::SoundBuffer>* getSounds();
	sf::Font* getFont();

	void setRootFolder(std::string folder);
	std::string getRootFolder(void);

	void setTileSize(unsigned short size);
	unsigned short getTileSize();

private:
	std::string _rootFolder;
	std::string _imagesFolder;
	std::string _fontsFolder;
	std::string _soundsFolder;

	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::SoundBuffer> _sounds;
	sf::Font _font;

	unsigned short _tileSize;
};
