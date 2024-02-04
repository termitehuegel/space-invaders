#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

#include "assetManager.h"
#include "gameState.h"
#include "projectile.h"

class Player {
public:
    /**
     * @param speed that the player moves at
     * @param reload_time the time between shots in milliseconds
     * @param invincibility_time the time the player is invincible for if hit in milliseconds
     */
    Player(float speed, unsigned int reload_time, unsigned int invincibility_time, AssetManager *asset_manager, GameState *game_state);

    void draw(sf::RenderWindow *window);

    void update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles,
                std::vector<Projectile *> *enemy_projectiles);

private:
    AssetManager *asset_manager;
    GameState *game_state;
    sf::Sprite sprite;
    float speed;
    unsigned int reload_cooldown;
    /**
     * The time in milliseconds between shots.
     */
    unsigned int reload_time;
    bool display;
    unsigned int invincibility_cooldown;
    /**
     * The time in milliseconds the player is invincible for.
     */
    unsigned int invincibility_time;
    /**
     * The time in milliseconds between changing the visibility of the player if he is invincible.
     */
    unsigned int invincibility_display_time;

    /**
     * Reduces all cooldowns
     */
    void updateTimers(sf::Time delta_time);

    /**
     * Evaluates player input and controls the player in response.
     */
    void updateControl(sf::Time delta_time, std::vector<Projectile *> *player_projectiles);

    /**
     * Evaluates if the player collides with any projectiles and reduces health accordingly.
     */
    void updateCollision(std::vector<Projectile *> *enemy_projectiles);

    /**
     * Changes the visibility of the player when the invincibility cooldown is over.
     */
    void updateInvincibilityBlinking();
};

#endif