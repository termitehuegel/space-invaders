#ifndef SPACE_INVADERS_PROJECTILE_H
#define SPACE_INVADERS_PROJECTILE_H

#include "assetManager.h"

class Projectile {
public:
    Projectile(float speed, float x, float y, AssetManager *asset_manager);

    void draw(sf::RenderWindow *window);

    void update(sf::Time delta_time);

    bool isInBound();

    bool collidesWith(sf::FloatRect bounds);

    sf::Rect<float> getBounds();

private:
    float speed;
    sf::Sprite sprite;
    bool in_bound;
};
#endif