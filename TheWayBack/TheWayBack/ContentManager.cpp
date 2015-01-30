#include "ContentManager.h"

ContentManager::ContentManager()
{
	_rootDir = "";
	_soundsDir = "";
	_fontsDir = "";
	_imagesDir = "";
	_tileSize = 32;
}

ContentManager::~ContentManager()
{
	_textures.clear();
}

void ContentManager::loadContent()
{
	addTexture("newchar02-2.png", "char1");
	addTexture("actor001.png", "char2");
	addTexture("newchar01-1.png", "char3");
	addTexture("newchar05-5.png", "char4");
	addTexture("dark_effect_001.png", "loading");
	addTexture("slash_effect_002.png", "loading2");
	// map tilesets
	addTexture("tile21.png", "tile21");
	addTexture("tilea2.png", "tilea2");
	addTexture("japanese.png", "japanese");
	addTexture("tilea4.png", "tilea4");


	addSound("collect.ogg", "collect");

	addFont("default.ttf", "mini");
}

void ContentManager::addTexture(std::string file, std::string name)
{
	sf::Texture texture;

	if (!texture.loadFromFile(_imagesDir + file))
	{
		texture.loadFromFile(_imagesDir + "unknown.png");
	}

	_textures[name] = texture;
}

void ContentManager::addTexture(std::string file, std::string name, sf::IntRect rect)
{
	sf::Texture texture;

	if (!texture.loadFromFile(_imagesDir + file, rect))
	{
		texture.loadFromFile(_imagesDir + "unknown.png");
	}

	_textures[name] = texture;
}

void ContentManager::addSound(std::string file, std::string name)
{
	sf::SoundBuffer soundBuffer;

	if (!soundBuffer.loadFromFile(_soundsDir + file))
	{
		soundBuffer.loadFromFile(_soundsDir + "unknown.ogg");
	}

	_sounds[name] = soundBuffer;
}

void ContentManager::addFont(std::string file, std::string name)
{
	sf::Font font;

	if (!font.loadFromFile(_fontsDir + file))
	{
		font.loadFromFile(_fontsDir + "default.ttf");
	}

	_font = font;
}

std::map <std::string, sf::Texture>* ContentManager::getTextures()
{
	return &_textures;
}

std::map <std::string, sf::SoundBuffer>* ContentManager::getSounds()
{
	return &_sounds;
}

sf::Font* ContentManager::getFont()
{
	return &_font;
}

void ContentManager::setRootFolder(std::string folder)
{
	_rootDir = folder + "/";
	_soundsDir = _rootDir + "Sounds/";
	_fontsDir = _rootDir + "Fonts/";
	_imagesDir = _rootDir + "Images/";
}
std::string ContentManager::getRootFolder()
{
	return _rootDir;
}

void ContentManager::setTileSize(unsigned short size)
{
	_tileSize = size;
}
unsigned short ContentManager::getTileSize()
{
	return _tileSize;
}