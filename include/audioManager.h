#ifndef SPACE_INVADERS_AUDIOMANAGER_H
#define SPACE_INVADERS_AUDIOMANAGER_H

#include <SFML/Audio.hpp>

class AudioManager {
public:
    AudioManager();

    void setMusicVolume(float volume);

    void setSFXVolume(float volume);

    void setMusicEnabled(bool enable);

    void playShootSFX();

private:
    sf::Music music;
    sf::SoundBuffer shoot_sound_buffer;
    sf::Sound shoot_sound;
};

#endif