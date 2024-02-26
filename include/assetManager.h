#ifndef SPACE_INVADERS_ASSETMANAGER_H
#define SPACE_INVADERS_ASSETMANAGER_H

#include <string>
#include <map>
#include "SFML/Graphics.hpp"
#include "audioManager.h"

typedef std::map<std::string, sf::Texture*> TextureMap;
typedef std::map<std::string, sf::Font*> FontMap;
typedef std::map<std::string, sf::Image*> ImageMap;

/**
 * The AssetManager is responsible for loading, unloading and providing assets such as textures, fonts, images and audio.
 */
class AssetManager
{
public:
    /**
     * @param asset_base_path searches for needed assets under this base path
     */
    AssetManager(std::string asset_base_path);

    AssetManager(const AssetManager& asset_manager);

    ~AssetManager();

    AudioManager* getAudioManager();

    const TextureMap* getTextures();

    const FontMap* getFonts();

    const ImageMap* getImages();

private:
    AudioManager* audio_manager;
    TextureMap textures;
    FontMap fonts;
    ImageMap images;

    void loadTexture(const std::string& key, const std::string& file_path);

    void loadFont(const std::string& key, const std::string& file_path);

    void loadImage(const std::string& key, const std::string& file_path);
};

#endif