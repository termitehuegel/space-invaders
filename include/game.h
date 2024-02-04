#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

#include "hud.h"
#include "player.h"
#include "enemyController.h"
#include "base.h"

/**
 * The Game class controls the all game specific elements and updates them when needed.
 */
class Game
{
public:
    /**
     * @param highscore the starting highscore
     * @param quit_time the time the player needs to hold escape to quit the game
     */
    Game(AssetManager* asset_manger, unsigned int highscore, unsigned int quit_time);

    ~Game();

    void update(sf::Time delta_time);

    void draw(sf::RenderWindow* window);

    /**
     * @return if the game is over
     */
    bool gameOver() const;

    /**
     * @return the current highscore
     */
    unsigned int highscore() const;

private:
    AssetManager* asset_manager;
    GameState game_state;
    HUD* hud;
    std::vector<Projectile*> player_projectiles;
    std::vector<Projectile*> enemy_projectiles;
    Base* bases[5];
    Player* player;
    EnemyController* enemy_controller;
    sf::Sprite background;
    unsigned int fps;
    unsigned int quit_cooldown;
    /**
     * The time the player needs to hold escape to quit the game.
     */
    unsigned int quit_time;

    /**
     * Checks all projectiles for potential collisions and removes them if necessary.
     */
    void updateProjectileCollision();

    /**
     * Checks if the current score is higher than the highscore and updates the highscore accordingly
     */
    void updateHighScore();

    /**
     * Reduces the quit cooldown if escape is pressed.
     */
    void updateQuit(sf::Time delta_time);
};

#endif