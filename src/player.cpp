#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "header/projectile.h"
#include "header/player.h"

Player::Player(float speed, int reload_time, AssetManager* asset_manager, GameState* game_state) {
    this->asset_manager = asset_manager;
    this->game_state = game_state;
    this->speed = speed;
    sprite.setTexture(*asset_manager->getTextures()->at("player"));
    sprite.setPosition(1920/2 - sprite.getTextureRect().getSize().y/2, 980);
    cooldown = 0;
    this->reload_time = reload_time;
}

void Player::draw(sf::RenderWindow *window) {
    window->draw(sprite);
}

void Player::update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles, std::vector<Projectile *> *enemy_projectiles) {
    updateControl(delta_time, player_projectiles);
    updateCollision(enemy_projectiles);
}

void Player::updateControl(sf::Time delta_time, std::vector<Projectile *> *player_projectiles) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.setPosition(std::max(sprite.getPosition().x - speed * delta_time.asMilliseconds(), 0.0f),
                           sprite.getPosition().y);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.setPosition(
                std::min(sprite.getPosition().x + speed * delta_time.asMilliseconds(), 1920.0f - sprite.getTextureRect().getSize().x),
                sprite.getPosition().y);
    }

    cooldown -= delta_time.asMilliseconds();
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && cooldown <= 0) {
        cooldown = reload_time;
        Projectile *projectile = new Projectile(-1.0f, sprite.getPosition().x + sprite.getTextureRect().getSize().y/2 - 8,
                                                sprite.getPosition().y - 1, asset_manager);
        player_projectiles->push_back(projectile);
    }
}

void Player::updateCollision(std::vector<Projectile *> *enemy_projectiles) {
    for (std::vector<Projectile*>::iterator iter = enemy_projectiles->begin(); iter != enemy_projectiles->end(); iter++) {
        if ((*iter)->collidesWith(sprite.getGlobalBounds())) {
            game_state->lives--;
            delete *iter;
            enemy_projectiles->erase(iter);
            break;
        }
    }
    if (game_state->lives == 0) {
        game_state->game_over = true;
    }
}
