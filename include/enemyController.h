#ifndef SPACE_INVADERS_ENEMYCONTROLLER_H
#define SPACE_INVADERS_ENEMYCONTROLLER_H

#include "enemy.h"
#include "projectile.h"
#include "gameState.h"

class EnemyController {
public:
    EnemyController(unsigned int reload_time, float acceleration, float speed, float step, GameState *game_state,
                    AssetManager *asset_manager);

    ~EnemyController();

    void update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles,
                std::vector<Projectile *> *enemy_projectiles);

    void draw(sf::RenderWindow *window);

private:
    AssetManager *asset_manager;
    float speed;
    float acceleration;
    Enemy *enemies[11][5];
    bool change_direction;
    float step;
    unsigned int reload_cooldown;
    unsigned int reload_time;
    unsigned int animation_cooldown;
    unsigned int animation_time;
    GameState *game_state;

    void updateTimers(sf::Time delta_time);

    void updateMovement(sf::Time delta_time);

    void updateCollision(std::vector<Projectile *> *player_projectiles);

    void updateAnimation();

    void shoot(std::vector<Projectile *> *enemy_projectiles);

    bool playerReached();

    bool isEmpty();

    void reset();
};

#endif