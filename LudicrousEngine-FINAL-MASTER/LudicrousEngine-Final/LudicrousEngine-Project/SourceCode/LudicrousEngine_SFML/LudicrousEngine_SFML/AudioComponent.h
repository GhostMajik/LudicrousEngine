#pragma once

#include <SFML/Audio.hpp>


class AudioComponent
{
public:
	AudioComponent();
	~AudioComponent();
	static void Initialize();
	static void PlayMusic(std::string filename);
	static void PlaySfx(std::string filename);
	static void StopMusic();
private:
	static sf::SoundBuffer buffer;
	static sf::Music music;
	static sf::Sound sound;
};