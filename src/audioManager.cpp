#include "../include/audioManager.h"

AudioManager::AudioManager() {
    music.openFromFile("assets/audio/space-invaders.ogg");
    music.setLoop(true);

    shoot_sound_buffer.loadFromFile("assets/audio/shoot.ogg");
    shoot_sound.setBuffer(shoot_sound_buffer);
}

void AudioManager::setMusicVolume(float volume) {
    music.setVolume(volume);
}

void AudioManager::setSFXVolume(float volume) {
    shoot_sound.setVolume(volume);
}

void AudioManager::setMusicEnabled(bool enable) {
    if (enable) {
        music.play();
    } else {
        music.stop();
    }
}

void AudioManager::playShootSFX() {
    shoot_sound.play();
}
