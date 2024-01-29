#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

#include "hud.h"
#include "player.h"
#include "enemyController.h"

class Game {
private:
    AssetManager *asset_manager;
    GameState game_state;
    HUD *hud;
    std::vector<Projectile *> player_projectiles;
    std::vector<Projectile *> enemy_projectiles;
    Player *player;
    EnemyController *enemy_controller;
    sf::Sprite background;
    unsigned int fps;
    int quit_time;

    void projectileCollision();

    void updateHighScore();

    void updateQuit(sf::Time delta_time);

public:
    Game(AssetManager *asset_manger, unsigned int highscore);

    void update(sf::Time delta_time);

    void draw(sf::RenderWindow *window);

    bool gameOver() const;

    unsigned int highscore() const;
};

#endif