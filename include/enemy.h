#ifndef SPACE_INVADERS_ENEMY_H
#define SPACE_INVADERS_ENEMY_H

#include "SFML/Graphics.hpp"
#include "projectile.h"

/**
 * Instances of this class represent a singular enemy.
 */
class Enemy
{
public:
    /**
     * @param texture that the enemy sprite should have (should be of size 192x64 [3 textures of 64x64 each])
     * @param x coordinate for the sprite to be drawn to (mind the size of the texture)
     * @param y coordinate for the sprite to be drawn to (mind the size of the texture)
     */
    Enemy(sf::Texture* texture, float x, float y);

    void setPosition(float x, float y);

    sf::Vector2<float> getPosition() const;

    /**
     * Changes the displayed texture to the next 64x64 texture
     */
    void animationStep();

    void draw(sf::RenderWindow* window) const;

    /**
     * Checks if one of the provided projectiles has collided with this enemy and removes the projectile if so.
     * @return true if a projectile collided with the base fragment and false otherwise
     */
    bool detectCollision(std::vector<Projectile*>* projectiles);

    /**
     * Creates a new projectile below the enemy that travels downward.
     * @return a pointer to the newly instanced projectile
     */
    Projectile* shoot(AssetManager* asset_manager) const;

private:
    sf::Sprite sprite;
};

#endif