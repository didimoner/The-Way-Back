#pragma once
#include "SFML\Audio.hpp"
#include <map>

class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	void addSound(sf::SoundBuffer &soundBuffer, std::string name);
	void play(std::string name);
	void pause(std::string name);
	void stop(std::string name);

	void setVolume(std::string name, float volume);
	float getVolume(std::string name);

	void setPlayingOffset(std::string name, float offset);
	float getPlayingOffset(std::string name);

	void setLoop(std::string name, bool flag);

private:
	std::map<std::string, sf::Sound> _sounds;
};
