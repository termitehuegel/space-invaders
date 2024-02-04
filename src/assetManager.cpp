#include "../include/assetManager.h"

AssetManager::AssetManager(std::string asset_base_path)
{
    audio_manager = new AudioManager(asset_base_path + "/audio");
    audio_manager->setSFXVolume(50);
    audio_manager->setMusicVolume(10);
    audio_manager->setMusicEnabled(true);

    loadTexture("background-menu", asset_base_path + "/textures/backgroundMenu.png");
    loadTexture("background", asset_base_path + "/textures/background.png");
    loadTexture("player", asset_base_path + "/textures/player.png");
    loadTexture("projectile", asset_base_path + "/textures/projectile.png");
    loadTexture("enemy-1", asset_base_path + "/textures/enemy1.png");
    loadTexture("enemy-2", asset_base_path + "/textures/enemy2.png");
    loadTexture("enemy-3", asset_base_path + "/textures/enemy3.png");
    loadTexture("base-fragment-1", asset_base_path + "/textures/baseFragment1.png");
    loadTexture("base-fragment-2", asset_base_path + "/textures/baseFragment2.png");
    loadTexture("base-fragment-3", asset_base_path + "/textures/baseFragment3.png");
    loadTexture("base-fragment-4", asset_base_path + "/textures/baseFragment4.png");
    loadTexture("base-fragment-5", asset_base_path + "/textures/baseFragment5.png");
    loadTexture("base-fragment-6", asset_base_path + "/textures/baseFragment6.png");

    loadFont("cour", asset_base_path + "/fonts/cour.ttf");

    loadImage("icon", asset_base_path + "/icons/icon.png");
}

AssetManager::~AssetManager()
{
    delete audio_manager;
    for (std::pair<std::string, sf::Texture*> map_entry: textures)
    {
        delete map_entry.second;
    }
    for (std::pair<std::string, sf::Font*> map_entry: fonts)
    {
        delete map_entry.second;
    }
    for (std::pair<std::string, sf::Image*> map_entry: images)
    {
        delete map_entry.second;
    }
}

AudioManager* AssetManager::getAudioManager()
{
    return audio_manager;
}

const TextureMap* AssetManager::getTextures()
{
    return &textures;
}

const FontMap* AssetManager::getFonts()
{
    return &fonts;
}

const ImageMap* AssetManager::getImages()
{
    return &images;
}

void AssetManager::loadTexture(const std::string& key, const std::string& file_path)
{
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(file_path);
    textures.insert(TextureMap::value_type(key, texture));
}

void AssetManager::loadFont(const std::string& key, const std::string& file_path)
{
    sf::Font* font = new sf::Font();
    font->loadFromFile(file_path);
    fonts.insert(FontMap::value_type(key, font));
}

void AssetManager::loadImage(const std::string& key, const std::string& file_path)
{
    sf::Image* image = new sf::Image();
    image->loadFromFile(file_path);
    images.insert(ImageMap::value_type(key, image));
}