#ifndef SPACE_INVADERS_BASE_H
#define SPACE_INVADERS_BASE_H

#include "assetManager.h"
#include "baseFragment.h"
#include "projectile.h"

/**
 * This class represents a Base that the player might hide behind.
 * It mainly functions as a container for the base fragments it consist of.
 */
class Base
{
public:
    Base(AssetManager* asset_manager, float x, float y);

    Base(const Base& base);

    ~Base();

    void update(std::vector<Projectile*>* enemy_projectiles, std::vector<Projectile*>* player_projectiles);

    void draw(sf::RenderWindow* window) const;

private:
    /**
     * This base fragment array contains references to all base fragments of this base.
     */
    BaseFragment* base_fragments[6];
};

#endif