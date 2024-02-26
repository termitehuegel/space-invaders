#include "../include/audioManager.h"

AudioManager::AudioManager(std::string base_path)
{
    this->base_path = base_path;
    music.openFromFile(base_path + "/space-invaders.ogg");
    music.setLoop(true);

    shoot_sound_buffer.loadFromFile(base_path + "/shoot.ogg");
    shoot_sound.setBuffer(shoot_sound_buffer);

    hit_sound_buffer.loadFromFile(base_path + "/hit.ogg");
    hit_sound.setBuffer(hit_sound_buffer);

    game_over_sound_buffer.loadFromFile(base_path + "/game_over.ogg");
    game_over_sound.setBuffer(game_over_sound_buffer);
}

AudioManager::AudioManager(const AudioManager& audio_manager)
{
    base_path = audio_manager.base_path;
    //sf::Music does not have a copy constructor, thus it is loaded again
    music.openFromFile(base_path+ "/space-invaders.ogg");
    music.setVolume(audio_manager.music.getVolume());
    music.setLoop(audio_manager.music.getLoop());
    music.setPosition(audio_manager.music.getPosition());
    shoot_sound_buffer = audio_manager.shoot_sound_buffer;
    shoot_sound.setBuffer(shoot_sound_buffer);
    hit_sound_buffer = audio_manager.hit_sound_buffer;
    hit_sound.setBuffer(hit_sound_buffer);
    game_over_sound_buffer = audio_manager.game_over_sound_buffer;
    game_over_sound.setBuffer(game_over_sound_buffer);
    game_over_sound.setBuffer(game_over_sound_buffer);
}

void AudioManager::setMusicVolume(float volume)
{
    music.setVolume(volume);
}

void AudioManager::setSFXVolume(float volume)
{
    shoot_sound.setVolume(volume);
}

void AudioManager::setMusicEnabled(bool enable)
{
    if (enable)
    {
        music.play();
    } else
    {
        music.stop();
    }
}

void AudioManager::playShootSFX()
{
    shoot_sound.play();
}

void AudioManager::playHitSFX()
{
    hit_sound.play();
}

void AudioManager::playGameOverSFX()
{
    game_over_sound.play();
}