#ifndef SPACE_INVADERS_BASE_H
#define SPACE_INVADERS_BASE_H

#include "assetManager.h"
#include "baseFragment.h"
#include "projectile.h"

class Base {
public:
    Base(AssetManager *asset_manager, float x, float y);

    ~Base();

    void update(std::vector<Projectile*>* enemy_projectiles, std::vector<Projectile*>* player_projectiles);

    void draw(sf::RenderWindow *window);
private:
    BaseFragment* base_fragments[6];
};

#endif