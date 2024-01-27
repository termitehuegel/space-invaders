#ifndef SPACE_INVADERS_PROJECTILE_H
#define SPACE_INVADERS_PROJECTILE_H


#include "assetManager.h"

class Projectile {
private:
    float speed;
    sf::Sprite sprite;
    bool in_bound;
public:
    Projectile(float speed, float x, float y, AssetManager* asset_manager);

    void draw(sf::RenderWindow *window);

    void update(sf::Time delta_time);

    float getSpeed();

    bool isInBound();

    bool collidesWith(sf::FloatRect bounds);
};

#endif