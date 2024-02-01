#include "header/assetManager.h"

AssetManager::AssetManager(const std::string &asset_base_path) {
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

void AssetManager::loadTexture(const std::string &key, const std::string &file_path) {
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile(file_path);
    textures.insert(TextureMap::value_type(key, texture));
}

void AssetManager::loadFont(const std::string &key, const std::string &file_path) {
    sf::Font *font = new sf::Font();
    font->loadFromFile(file_path);
    fonts.insert(FontMap::value_type(key, font));
}

void AssetManager::loadImage(const std::string &key, const std::string &file_path) {
    sf::Image *image = new sf::Image();
    image->loadFromFile(file_path);
    images.insert(ImageMap::value_type(key, image));
}

AssetManager::~AssetManager() {
    for (std::pair<std::string, sf::Texture *> map_entry: textures) {
        delete map_entry.second;
    }
    for (std::pair<std::string, sf::Font *> map_entry: fonts) {
        delete map_entry.second;
    }
    for (std::pair<std::string, sf::Image *> map_entry: images) {
        delete map_entry.second;
    }
}