#pragma once

#include <SFML/Audio.hpp>
#include <string>


class AudioComponent {
private:
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	

public:
	AudioComponent();
	void SetSound(std::string sFilename);
	void SetVolume(float volume);
	void SetPitch(float pitch);
	void PlaySound();
	void PauseSound();
	void StopSound();
};
