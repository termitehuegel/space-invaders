#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

#include "assetManager.h"
#include "gameState.h"
#include "projectile.h"

class Player {
private:
    AssetManager* asset_manager;
    GameState* game_state;
    sf::Sprite sprite;
    float speed;
    int cooldown;
    int reload_time;

    void updateControl(sf::Time delta_time, std::vector<Projectile *> *player_projectiles);
    void updateCollision(std::vector<Projectile*>* enemy_projectiles);
public:
    Player(float speed, int reload_time, AssetManager* asset_manager, GameState* game_state);
    void draw(sf::RenderWindow *window);
    void update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles, std::vector<Projectile *> *enemy_projectiles);
};

#endif