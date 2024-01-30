#include "header/assetManager.h"

AssetManager::AssetManager(std::string asset_base_path) {
    loadTexture("background-menu", asset_base_path + "/textures/backgroundMenu.png");
    loadTexture("background", asset_base_path + "/textures/background.png");
    loadTexture("player", asset_base_path + "/textures/player.png");
    loadTexture("projectile", asset_base_path + "/textures/projectile.png");
    loadTexture("enemy1", asset_base_path + "/textures/enemy1.png");
    loadTexture("enemy2", asset_base_path + "/textures/enemy2.png");
    loadTexture("enemy3", asset_base_path + "/textures/enemy3.png");

    loadFont("cour", asset_base_path + "/fonts/cour.ttf");

    loadImage("icon", asset_base_path + "/icons/icon.png");
}

const TextureMap *AssetManager::getTextures() {
    return &textures;
}

const FontMap *AssetManager::getFonts() {
    return &fonts;
}

const ImageMap *AssetManager::getImages() {
    return &images;
}

void AssetManager::loadTexture(std::string key, std::string file_path) {
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile(file_path);
    textures.insert(TextureMap::value_type(key, texture));
}

void AssetManager::loadFont(std::string key, std::string file_path) {
    sf::Font *font = new sf::Font();
    font->loadFromFile(file_path);
    fonts.insert(FontMap::value_type(key, font));
}

void AssetManager::loadImage(std::string key, std::string file_path) {
    sf::Image *image = new sf::Image();
    image->loadFromFile(file_path);
    images.insert(ImageMap::value_type(key, image));
}


