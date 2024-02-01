#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

#include "assetManager.h"
#include "gameState.h"
#include "projectile.h"

class Player {
public:
    Player(float speed, int reload_time, int invincibility_time, AssetManager *asset_manager, GameState *game_state);

    void draw(sf::RenderWindow *window);

    void update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles,
                std::vector<Projectile *> *enemy_projectiles);

private:
    AssetManager *asset_manager;
    GameState *game_state;
    sf::Sprite sprite;
    bool display;
    float speed;
    unsigned int reload_cooldown;
    int reload_time;
    int invincibility_time;
    unsigned int invincibility_cooldown;
    unsigned int invincivility_display_time;

    void updateTimers(sf::Time delta_time);

    void updateInvincibilityBlinking();

    void updateControl(sf::Time delta_time, std::vector<Projectile *> *player_projectiles);

    void updateCollision(std::vector<Projectile *> *enemy_projectiles);
};

#endif