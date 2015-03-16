#include "ContentManager.h"

ContentManager::ContentManager()
{
	_rootDir = "";
	_soundsDir = "";
	_fontsDir = "";
	_imagesDir = "";
	_resourcesDir = "";
	_tileSize = 32;
}

ContentManager::~ContentManager()
{
	_textures.clear();
	_sounds.clear();
}

void ContentManager::loadContent(std::string screenName)
{
	std::ifstream file;
	std::string realName = "";
	std::string shortName = "";

	// —читываем текстуры
	file.open(_resourcesDir + screenName + ".txl");
	if (!file)
	{
		std::cout << "Can not open file: " << _resourcesDir + screenName + ".txl" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			file >> realName >> shortName;
			if (!realName.empty())
				addTexture(realName, shortName);
		}

		file.close();
	}

	realName = "";
	shortName = "";

	// считываем звуки
	file.open(_resourcesDir + screenName + ".snl");
	if (!file)
	{
		std::cout << "Can not open file: " << _resourcesDir + screenName + ".snl" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			file >> realName >> shortName;
			if (!realName.empty())
				addSound(realName, shortName);
		}

		file.close();
	}

	realName = "";
	shortName = "";

	// считываем шрифты
	file.open(_resourcesDir + screenName + ".fnl");
	if (!file)
	{
		std::cout << "Can not open file: " << _resourcesDir + screenName + ".fnl" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			file >> realName >> shortName;
			if (!realName.empty())
				addFont(realName, shortName);
		}

		file.close();
	}
	
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

	_fonts[name] = font;
}

std::map <std::string, sf::Texture>* ContentManager::getTextures()
{
	return &_textures;
}

std::map <std::string, sf::SoundBuffer>* ContentManager::getSounds()
{
	return &_sounds;
}

std::map <std::string, sf::Font>* ContentManager::getFonts()
{
	return &_fonts;
}

void ContentManager::setRootFolder(std::string folder)
{
	_rootDir = folder + "/";
	_soundsDir = _rootDir + "Sounds/";
	_fontsDir = _rootDir + "Fonts/";
	_imagesDir = _rootDir + "Images/";
	_resourcesDir = _rootDir + "Resources/";
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

void ContentManager::clear()
{
	_textures.clear();
	_sounds.clear();
}