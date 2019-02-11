#pragma once

#include <SFML/Audio.hpp>
#include <string>


class MusicComponent {
private:
	sf::Music music;


public:
	MusicComponent();
	void SetMusic(std::string sFilename);
	void SetVolume(float volume);
	void SetPitch(float pitch);
	void PlayMusic();
	void PauseMusic();
	void StopMusic();
};
