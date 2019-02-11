#include "AudioComponent.h"
#include <string>


AudioComponent::AudioComponent() {
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
};


void AudioComponent::SetSound(std::string filename) {
	if (!soundBuffer.loadFromFile("filename")) {
		sound.setBuffer(soundBuffer);
		
	}
}

void AudioComponent::SetVolume(float volume) {
	sound.setVolume(volume);
}

void AudioComponent::SetPitch(float pitch) {
	sound.setPitch(pitch);
}


void AudioComponent::PlaySound() {
	sound.play();
}

void AudioComponent::PauseSound() {
	sound.pause();
}

void AudioComponent::StopSound() {
	sound.stop();
}
