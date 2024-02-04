#include "../include/base.h"

Base::Base(AssetManager *asset_manager, float x, float y) {
    // The coordinates of the base fragments are determined by counting the pixels from the start of
    // the base (texture) to the start of the fragments texture
    base_fragments[0] = new BaseFragment(asset_manager->getTextures()->at("base-fragment-1"), x + 45, y + 5);
    base_fragments[1] = new BaseFragment(asset_manager->getTextures()->at("base-fragment-2"), x + 35, y + 21);
    base_fragments[2] = new BaseFragment(asset_manager->getTextures()->at("base-fragment-3"), x + 20, y + 0);
    base_fragments[3] = new BaseFragment(asset_manager->getTextures()->at("base-fragment-4"), x + 10, y + 10);
    base_fragments[4] = new BaseFragment(asset_manager->getTextures()->at("base-fragment-5"), x + 0, y + 25);
    base_fragments[5] = new BaseFragment(asset_manager->getTextures()->at("base-fragment-6"), x + 0, y + 0);
}

Base::~Base() {
    for (BaseFragment *base_fragment: base_fragments) {
        if (base_fragment == nullptr) {
            continue;
        }
        delete base_fragment;
    }
}

void Base::update(std::vector<Projectile *> *enemy_projectiles, std::vector<Projectile *> *player_projectiles) {
    for (int i = 0; i < 6; i++) {
        if (base_fragments[i] == nullptr) {
            continue;
        }
        if (base_fragments[i]->detectCollision(enemy_projectiles, player_projectiles)) {
            delete base_fragments[i];
            base_fragments[i] = nullptr;
        }
    }
}

void Base::draw(sf::RenderWindow *window) const {
    for (BaseFragment *base_fragment: base_fragments) {
        if (base_fragment == nullptr) {
            continue;
        }
        base_fragment->draw(window);
    }
}
