#ifndef SPACE_INVADERS_ASSETMANAGER_H
#define SPACE_INVADERS_ASSETMANAGER_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

typedef std::map<std::string, sf::Texture *> TextureMap;
typedef std::map<std::string, sf::Font *> FontMap;
typedef std::map<std::string, sf::Image *> ImageMap;

class AssetManager {
private:
    TextureMap textures;
    FontMap fonts;
    ImageMap images;

    void loadTexture(std::string key, std::string file_path);

    void loadFont(std::string key, std::string file_path);

    void loadImage(std::string key, std::string file_path);

public:
    AssetManager(std::string asset_base_path);

    const TextureMap *getTextures();

    const FontMap *getFonts();

    const ImageMap *getImages();
};

#endif