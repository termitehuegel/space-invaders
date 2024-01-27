#ifndef SPACE_INVADERS_ASSETMANAGER_H
#define SPACE_INVADERS_ASSETMANAGER_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

typedef std::map<std::string, sf::Texture *> TextureMap;
typedef std::map<std::string, sf::Font *> FontMap;

class AssetManager {
private:
    TextureMap textures;
    FontMap fonts;
    void loadTexture(std::string key, std::string file_path);
    void loadFont(std::string key, std::string file_path);
public:
    AssetManager(std::string asset_base_path);
    const TextureMap* getTextures();
    const FontMap* getFonts();
};

#endif