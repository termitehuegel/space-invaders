#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

#include "hud.h"
#include "player.h"
#include "enemyController.h"
#include "base.h"

class Game {
public:
    Game(AssetManager *asset_manger, unsigned int highscore, unsigned int quit_time);

    ~Game();

    void update(sf::Time delta_time);

    void draw(sf::RenderWindow *window);

    bool gameOver() const;

    unsigned int highscore() const;

private:
    AssetManager *asset_manager;
    GameState game_state;
    HUD *hud;
    std::vector<Projectile *> player_projectiles;
    std::vector<Projectile *> enemy_projectiles;
    Base *bases[5];
    Player *player;
    EnemyController *enemy_controller;
    sf::Sprite background;
    unsigned int fps;
    unsigned int quit_cooldown;
    unsigned int quit_time;

    void projectileCollision();

    void updateHighScore();

    void updateQuit(sf::Time delta_time);
};

#endif