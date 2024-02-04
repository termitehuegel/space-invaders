#include "../include/audioManager.h"

AudioManager::AudioManager(const std::string &audio_base_path) {
    music.openFromFile(audio_base_path + "/space-invaders.ogg");
    music.setLoop(true);

    shoot_sound_buffer.loadFromFile(audio_base_path + "/shoot.ogg");
    shoot_sound.setBuffer(shoot_sound_buffer);

    hit_sound_buffer.loadFromFile(audio_base_path + "/hit.ogg");
    hit_sound.setBuffer(hit_sound_buffer);

    game_over_sound_buffer.loadFromFile(audio_base_path + "/game_over.ogg");
    game_over_sound.setBuffer(game_over_sound_buffer);
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

void AudioManager::playHitSFX() {
    hit_sound.play();
}

void AudioManager::playGameOverSFX() {
    game_over_sound.play();
}