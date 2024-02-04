#include <cmath>

#include "../include/game.h"

Game::Game(AssetManager *asset_manger, unsigned int highscore, unsigned int quit_time) {
    this->asset_manager = asset_manger;
    this->quit_time = quit_time;
    game_state = {false, 0, highscore, 3};
    hud = new HUD(asset_manager, &game_state);
    player = new Player(0.5f, 1500, 2500, asset_manager, &game_state);
    enemy_controller = new EnemyController(1500, 0.005f, 0.05f, 15, &game_state, asset_manager);
    background.setTexture(*asset_manager->getTextures()->at("background"));
    quit_cooldown = quit_time;

    for (int i = 0; i < 5; i++) {
        bases[i] = new Base(asset_manger, (float) (232 + 344 * i), 900.0f);
    }
}

Game::~Game() {
    delete hud;
    for (Projectile *projectile: player_projectiles) {
        delete projectile;
    }
    for (Projectile *projectile: enemy_projectiles) {
        delete projectile;
    }
    delete player;
    delete enemy_controller;
    for (Base *base: bases) {
        delete base;
    }
}

void Game::update(sf::Time delta_time) {
    fps = std::floor(1.0f / delta_time.asSeconds());
    player->update(delta_time, &player_projectiles, &enemy_projectiles);
    enemy_controller->update(delta_time, &player_projectiles, &enemy_projectiles);
    for (Base *base: bases) {
        base->update(&enemy_projectiles, &player_projectiles);
    }
    for (std::vector<Projectile *>::iterator iterator = player_projectiles.begin();
         iterator != player_projectiles.end();) {
        (*iterator)->update(delta_time);
        if (!(*iterator)->isInBound()) {
            delete *iterator;
            iterator = player_projectiles.erase(iterator);
        } else {
            iterator++;
        }
    }
    for (std::vector<Projectile *>::iterator iterator = enemy_projectiles.begin();
         iterator != enemy_projectiles.end();) {
        (*iterator)->update(delta_time);
        if (!(*iterator)->isInBound()) {
            delete *iterator;
            iterator = enemy_projectiles.erase(iterator);
        } else {
            iterator++;
        }
    }
    projectileCollision();
    updateHighScore();
    updateQuit(delta_time);
}

void Game::draw(sf::RenderWindow *window) {
    window->draw(background);
    hud->draw(window, fps);
    player->draw(window);
    enemy_controller->draw(window);
    for (Base *base: bases) {
        base->draw(window);
    }
    for (Projectile *projectile: player_projectiles) {
        if (projectile == nullptr) {
            continue;
        }
        projectile->draw(window);
    }
    for (Projectile *projectile: enemy_projectiles) {
        if (projectile == nullptr) {
            continue;
        }
        projectile->draw(window);
    }
}

bool Game::gameOver() const {
    return game_state.game_over;
}

void Game::projectileCollision() {
    for (std::vector<Projectile *>::iterator player_projectile_iter = player_projectiles.begin();
         player_projectile_iter != player_projectiles.end();) {
        bool next = true;
        for (std::vector<Projectile *>::iterator enemy_projectile_iter = enemy_projectiles.begin();
             enemy_projectile_iter != enemy_projectiles.end(); enemy_projectile_iter++) {
            if ((*player_projectile_iter)->collidesWith((*enemy_projectile_iter)->getBounds())) {
                delete *enemy_projectile_iter;
                delete *player_projectile_iter;
                enemy_projectiles.erase(enemy_projectile_iter);
                player_projectile_iter = player_projectiles.erase(player_projectile_iter);
                next = false;
                break;
            }
        }
        if (next) {
            player_projectile_iter++;
        }
    }
}

unsigned int Game::highscore() const {
    return game_state.highscore;
}

void Game::updateHighScore() {
    if (game_state.highscore < game_state.score) {
        game_state.highscore = game_state.score;
    }
}

void Game::updateQuit(sf::Time delta_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        quit_cooldown = quit_cooldown > delta_time.asMilliseconds() ? quit_cooldown - delta_time.asMilliseconds() : 0;
        if (quit_cooldown <= 0) {
            game_state.game_over = true;
        }
    } else {
        quit_cooldown = quit_time;
    }
}