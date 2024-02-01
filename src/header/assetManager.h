#ifndef SPACE_INVADERS_ASSETMANAGER_H
#define SPACE_INVADERS_ASSETMANAGER_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

typedef std::map<std::string, sf::Texture *> TextureMap;
typedef std::map<std::string, sf::Font *> FontMap;
typedef std::map<std::string, sf::Image *> ImageMap;

class AssetManager {
public:
    AssetManager(const std::string& asset_base_path);

    ~AssetManager();

    const TextureMap *getTextures();

    const FontMap *getFonts();

    const ImageMap *getImages();

private:
    TextureMap textures;
    FontMap fonts;
    ImageMap images;

    void loadTexture(const std::string& key, const std::string& file_path);

    void loadFont(const std::string& key, const std::string& file_path);

    void loadImage(const std::string& key, const std::string& file_path);
};
#endif