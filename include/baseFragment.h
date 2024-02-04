#ifndef SPACE_INVADERS_BASEFRAGMENT_H
#define SPACE_INVADERS_BASEFRAGMENT_H

#include <SFML/Graphics.hpp>
#include "projectile.h"

/**
 * A base fragment is a piece of the base that might be individually removed if hit.
 */
class BaseFragment {
public:
    /**
     * @param texture that the fragment sprite should have
     * @param x coordinate for the sprite to be drawn to (mind the size of the texture)
     * @param y coordinate for the sprite to be drawn to (mind the size of the texture)
     */
    BaseFragment(sf::Texture *texture, float x, float y);

    /**
     * Checks if one of the provides projectiles has collided with this fragment and removes the projectile if so.
     * @return true if a projectile collided with the base fragment and false otherwise
     */
    bool detectCollision(std::vector<Projectile *> *enemy_projectiles, std::vector<Projectile *> *player_projectiles);

    void draw(sf::RenderWindow *window) const;

private:
    sf::Sprite sprite;
};

#endif