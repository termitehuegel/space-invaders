#ifndef SPACE_INVADERS_ENEMYCONTROLLER_H
#define SPACE_INVADERS_ENEMYCONTROLLER_H

#include "enemy.h"
#include "projectile.h"
#include "gameState.h"

/**
 * The EnemyController is responsible for all enemies.
 * It manages the positions of the enemies, their animation steps, collisions and shooting.
 */
class EnemyController
{
public:
    /**
     * @param reload_time the time between shoots (multiple columns might shoot at once)
     * @param acceleration the speed that is added to the current speed after a enemy is killed
     * @param speed the starting speed of the enemies
     * @param step the length the enemies move towards the player when they reach the edge
     */
    EnemyController(unsigned int reload_time, float acceleration, float speed, float step, GameState* game_state,
                    AssetManager* asset_manager);

    ~EnemyController();

    void update(sf::Time delta_time, std::vector<Projectile*>* player_projectiles,
                std::vector<Projectile*>* enemy_projectiles);

    void draw(sf::RenderWindow* window);

private:
    AssetManager* asset_manager;
    float speed;
    float acceleration;
    Enemy* enemies[11][5];
    bool change_direction;
    float step;
    unsigned int reload_cooldown;
    /**
     * The time in milliseconds between shots.
     */
    unsigned int reload_time;
    unsigned int animation_cooldown;
    /**
     * The time in milliseconds between each animation step
     */
    unsigned int animation_time;
    GameState* game_state;

    /**
     * Reduces all cooldowns
     */
    void updateTimers(sf::Time delta_time);

    /**
     * Moves the enemies from one edge to the other.
     */
    void updateMovement(sf::Time delta_time);

    /**
     * Checks if any projectiles collide with an enemy and destroy both if so.
     */
    void updateCollision(std::vector<Projectile*>* player_projectiles);

    /**
     * Updates all animation steps of the enemies if the animation cooldown has ended.
     */
    void updateAnimation();

    /**
     * Allows the enemies to randomly shoot when there is no reload cooldown.
     * And appends the projectiles to the provided vector.
     */
    void shoot(std::vector<Projectile*>* enemy_projectiles);

    /**
     * @return true if the height of the player is reached and false otherwise
     */
    bool playerReached();

    /**
     * @return true if no enemies are left and false otherwise
     */
    bool isEmpty();

    /**
     * Resets the enemies and there speed back to the starting position
     */
    void reset();
};

#endif