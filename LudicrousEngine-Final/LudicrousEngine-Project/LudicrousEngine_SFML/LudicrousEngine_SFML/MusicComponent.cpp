#include "MusicComponent.h"
#include <string>


MusicComponent::MusicComponent() {
	sf::Music music;
};


void MusicComponent::SetMusic(std::string filename) {
	if (!music.openFromFile("filename")) {
		return
	}
	else
		PlayMusic();
}

void MusicComponent::SetVolume(float volume) {
	music.setVolume(volume);
}

void MusicComponent::SetPitch(float pitch) {
	music.setPitch(pitch);
}


void MusicComponent::PlayMusic() {
	music.play();
}

void MusicComponent::PauseMusic() {
	music.pause();
}

void MusicComponent::StopMusic() {
	music.stop();
}
