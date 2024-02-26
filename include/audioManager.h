#ifndef SPACE_INVADERS_AUDIOMANAGER_H
#define SPACE_INVADERS_AUDIOMANAGER_H

#include <SFML/Audio.hpp>

/**
 * This class is responsible for loading and playing music and sounds.
 * All instances of this class need to be destroyed before exiting the program to avoid a "device not closed" warning.
 */
class AudioManager
{
public:
    /**
     * @param asset_base_path searches for needed audio under this base path
     */
    AudioManager(std::string base_path);

    AudioManager(const AudioManager& audio_manager);

    void setMusicVolume(float volume);

    void setSFXVolume(float volume);

    /**
     * Enables or disables the background music depending on the provides parameter.
     * @param enable enables the music if true and disables it otherwise
     */
    void setMusicEnabled(bool enable);

    void playShootSFX();

    void playHitSFX();

    void playGameOverSFX();

private:
    std::string base_path;
    sf::Music music;
    sf::SoundBuffer shoot_sound_buffer;
    sf::Sound shoot_sound;
    sf::SoundBuffer hit_sound_buffer;
    sf::Sound hit_sound;
    sf::SoundBuffer game_over_sound_buffer;
    sf::Sound game_over_sound;
};

#endif