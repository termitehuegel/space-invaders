#include <cmath>

#include "header/game.h"

Game::Game(AssetManager *asset_manger, unsigned int highscore) {
    this->asset_manager = asset_manger;
    game_state = {false, 0, highscore, 3};
    hud = new HUD(asset_manager, &game_state);
    player = new Player(0.5f, 2500, asset_manager, &game_state);
    enemy_controller = new EnemyController(0.01f, 0.05f, 15, &game_state, asset_manager);
    background.setTexture(*asset_manager->getTextures()->at("background"));
}

void Game::update(sf::Time delta_time) {
    fps = std::floor(1.0f/delta_time.asSeconds());
    player->update(delta_time, &player_projectiles, &enemy_projectiles);
    enemy_controller->update(delta_time, &player_projectiles, &enemy_projectiles);
    for (std::vector<Projectile*>::iterator iterator = player_projectiles.begin(); iterator != player_projectiles.end();) {
        (*iterator)->update(delta_time);
        if (!(*iterator)->isInBound()) {
            delete *iterator;
            iterator = player_projectiles.erase(iterator);
        } else {
            iterator++;
        }
    }
    for (std::vector<Projectile*>::iterator iterator = enemy_projectiles.begin(); iterator != enemy_projectiles.end();) {
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
}

void Game::draw(sf::RenderWindow *window) {
    window->draw(background);
    hud->draw(window, fps);
    player->draw(window);
    enemy_controller->draw(window);
    for (Projectile* projectile : player_projectiles) {
        if (projectile == nullptr) {
            continue;
        }
        projectile->draw(window);
    }
    for (Projectile* projectile : enemy_projectiles) {
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
    for (std::vector<Projectile*>::iterator player_projectile_iter = player_projectiles.begin(); player_projectile_iter != player_projectiles.end();) {
        bool next = true;
        for (std::vector<Projectile*>::iterator enemy_projectile_iter = enemy_projectiles.begin(); enemy_projectile_iter != enemy_projectiles.end(); enemy_projectile_iter++) {
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
