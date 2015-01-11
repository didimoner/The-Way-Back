#include "SoundManager.h"

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
}

void SoundManager::addSound(sf::SoundBuffer &soundBuffer, std::string name)
{
	sf::Sound* pSound = new sf::Sound();

	pSound->setBuffer(soundBuffer);
	pSound->setLoop(false);

	_sounds[name] = *pSound;

	delete pSound;
}

void SoundManager::play(std::string name)
{
	_sounds[name].play();
}
void SoundManager::pause(std::string name)
{
	_sounds[name].pause();
}
void SoundManager::stop(std::string name)
{
	_sounds[name].stop();
}

void SoundManager::setVolume(std::string name, float volume)
{
	_sounds[name].setVolume(volume);
}
float SoundManager::getVolume(std::string name)
{
	return _sounds[name].getVolume();
}

void SoundManager::setPlayingOffset(std::string name, float offset)
{
	_sounds[name].setPlayingOffset(sf::seconds(offset));
}
float SoundManager::getPlayingOffset(std::string name)
{
	return _sounds[name].getPlayingOffset().asSeconds();
}

void SoundManager::setLoop(std::string name, bool flag)
{
	_sounds[name].setLoop(flag);
}