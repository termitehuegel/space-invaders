#ifndef SPACE_INVADERS_PROJECTILE_H
#define SPACE_INVADERS_PROJECTILE_H

#include "assetManager.h"

class Projectile
{
public:
    /**
     * @param speed that the projectile travels at (vertically). May be negative such that the projectile travels up.
     */
    Projectile(float speed, float x, float y, AssetManager* asset_manager);

    void draw(sf::RenderWindow* window) const;

    void update(sf::Time delta_time);

    /**
     * Checks if the projectile is still in the bounds of the window.
     * @return true if the projectile is in the window, false otherwise
     */
    bool isInBound() const;

    /**
     * Checks if the projectile collides with the provides bounds.
     * @param bounds that might collide with the projectile
     * @return true if the bounds collide or false otherwise
     */
    bool collidesWith(sf::FloatRect bounds) const;

    /**
     * @return the global bounds of the projectile
     */
    sf::Rect<float> getBounds() const;

private:
    float speed;
    sf::Sprite sprite;
    bool in_bound;
};

#endif