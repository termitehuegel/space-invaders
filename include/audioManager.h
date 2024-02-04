#ifndef SPACE_INVADERS_AUDIOMANAGER_H
#define SPACE_INVADERS_AUDIOMANAGER_H

#include <SFML/Audio.hpp>

class AudioManager {
public:
    AudioManager(const std::string &audio_base_path);

    void setMusicVolume(float volume);

    void setSFXVolume(float volume);

    void setMusicEnabled(bool enable);

    void playShootSFX();

    void playHitSFX();

    void playGameOverSFX();

private:
    sf::Music music;
    sf::SoundBuffer shoot_sound_buffer;
    sf::Sound shoot_sound;
    sf::SoundBuffer hit_sound_buffer;
    sf::Sound hit_sound;
    sf::SoundBuffer game_over_sound_buffer;
    sf::Sound game_over_sound;
};

#endif