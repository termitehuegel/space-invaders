#ifndef SPACE_INVADERS_ENEMYCONTROLLER_H
#define SPACE_INVADERS_ENEMYCONTROLLER_H

#include "enemy.h"
#include "projectile.h"
#include "gameState.h"

class EnemyController {
private:
    AssetManager *asset_manager;
    float speed;
    float acceleration;
    Enemy *enemies[11][5];
    bool change_direction;
    float step;
    unsigned int cooldown;
    int reload_time;
    GameState *game_state;

    void updateMovement(sf::Time delta_time);

    void updateCollision(sf::Time delta_time, std::vector<Projectile *> *player_projectiles);

    void shoot(sf::Time delta_time, std::vector<Projectile *> *enemy_projectiles);

    bool playerReached();

    bool isEmpty();

    void reset();

public:
    EnemyController(int reload_time, float acceleration, float speed, float step, GameState *game_state,
                    AssetManager *asset_manager);

    void update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles,
                std::vector<Projectile *> *enemy_projectiles);

    void draw(sf::RenderWindow *window);
};


#endif