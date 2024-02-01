#include <iostream>
#include "header/enemyController.h"

EnemyController::EnemyController(int reload_time, float acceleration, float speed, float step, GameState *game_state,
                                 AssetManager *asset_manager) {
    this->asset_manager = asset_manager;
    change_direction = false;
    this->acceleration = acceleration;
    this->speed = speed;
    this->step = step;
    this->reload_time = reload_time;
    this->game_state = game_state;
    cooldown = 0;
    reset();
}

void EnemyController::update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles,
                             std::vector<Projectile *> *enemy_projectiles) {
    updateMovement(delta_time);
    updateCollision(delta_time, player_projectiles);
    shoot(delta_time, enemy_projectiles);

    if (playerReached()) {
        game_state->game_over = true;
    }
}

void EnemyController::draw(sf::RenderWindow *window) {
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            if (enemies[x][y] == nullptr) {
                continue;
            }
            enemies[x][y]->draw(window);
        }
    }
}

void EnemyController::updateMovement(sf::Time delta_time) {
    if (change_direction) {
        speed *= -1;
    }

    bool border_reached = false;
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            if (enemies[x][y] == nullptr) {
                continue;
            }
            sf::Vector2<float> position = enemies[x][y]->getPosition();
            float new_x = position.x + speed * (float) delta_time.asMilliseconds();
            float new_y = position.y;
            if (change_direction) {
                new_y = position.y + step;
            }

            enemies[x][y]->setPosition(new_x, new_y);
            if ((new_x <= 0 && speed < 0) ||
                (new_x + 32.0f >= 1920 && speed > 0)) {
                border_reached = true;
            }
        }
    }
    if (change_direction) {
        change_direction = false;
    } else if (border_reached) {
        change_direction = true;
    }
}

void EnemyController::updateCollision(sf::Time delta_time, std::vector<Projectile *> *player_projectiles) {
    bool hit = false;
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            if (enemies[x][y] == nullptr) {
                continue;
            }
            if (enemies[x][y]->detectCollision(player_projectiles)) {
                hit = true;
                delete enemies[x][y];
                enemies[x][y] = nullptr;
                game_state->score += 100;
                if (speed >= 0) {
                    speed += acceleration;
                } else {
                    speed -= acceleration;
                }
            }
        }
    }
    if (isEmpty()) {
        reset();
        if (speed > 0) {
            speed = speed - 11 * 5 * acceleration;
        } else {
            speed = speed + 11 * 5 * acceleration;
        }
    }
}

void EnemyController::shoot(sf::Time delta_time, std::vector<Projectile *> *enemy_projectiles) {
    cooldown = cooldown > delta_time.asMilliseconds() ? cooldown - delta_time.asMilliseconds(): 0;
    if (cooldown <= 0) {
        for (int x = 0; x < 11; x++) {
            bool no_shoot = std::rand() % 5;
            if (no_shoot) {
                continue;
            }
            for (int y = 4; y >= 0; y--) {
                if (enemies[x][y] != nullptr) {
                    enemy_projectiles->push_back(enemies[x][y]->shoot(asset_manager));
                    cooldown = reload_time;
                    break;
                }
            }
        }
    }
}

bool EnemyController::playerReached() {
    for (int x = 0; x < 11; x++) {
        for (int y = 4; y >= 0; y--) {
            if (enemies[x][y] == nullptr) {
                continue;
            }
            return enemies[x][y]->getPosition().y >= 980;
        }
    }
    return false;
}

bool EnemyController::isEmpty() {
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            if (enemies[x][y] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

void EnemyController::reset() {
    for (int y = 0; y < 5; y++) {
        sf::Texture *texture;
        switch (y) {
            case 0:
                texture = asset_manager->getTextures()->at("enemy1");
                break;
            case 1:
            case 2:
                texture = asset_manager->getTextures()->at("enemy2");
                break;
            case 3:
            case 4:
                texture = asset_manager->getTextures()->at("enemy3");
                break;
            default:
                texture = asset_manager->getTextures()->at("enemy1");
                break;
        }
        for (int x = 0; x < 11; x++) {
            enemies[x][y] = new Enemy(texture, 150.0f + (float) x * 150, 200.0f + (float) y * 75.0f);
        }
    }
}
