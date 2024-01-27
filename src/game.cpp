#include "header/game.h"

Game::Game(AssetManager *asset_manger) {
    this->asset_manager = asset_manger;
    game_state = {false, 0, 0, 3};
    hud = new HUD(asset_manager, &game_state);
    player = new Player(0.5f, 2500, asset_manager, &game_state);
    enemy_controller = new EnemyController(0.01f, 0.05f, 15, &game_state, asset_manager);
    background.setTexture(*asset_manager->getTextures()->at("background"));
}

void Game::update(sf::Time delta_time) {
    fps = floor(1.0f/delta_time.asSeconds());
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

bool Game::gameOver() {
    return game_state.game_over;
}
