#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../include/projectile.h"
#include "../include/player.h"

Player::Player(float speed, unsigned int reload_time, unsigned int invincibility_time, AssetManager *asset_manager,
               GameState *game_state) {
    this->asset_manager = asset_manager;
    this->game_state = game_state;
    this->speed = speed;
    sprite.setTexture(*asset_manager->getTextures()->at("player"));
    sprite.setPosition(960.0f - (float) sprite.getTextureRect().getSize().y / 2.0f, 980.0f);
    this->reload_time = reload_time;
    reload_cooldown = 0;
    display = true;
    this->invincibility_time = invincibility_time;
    invincibility_cooldown = 0;
    invincibility_display_time = 0;
}

void Player::draw(sf::RenderWindow *window) {
    if (display) {
        window->draw(sprite);
    }
}

void Player::update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles,
                    std::vector<Projectile *> *enemy_projectiles) {
    updateTimers(delta_time);
    updateControl(delta_time, player_projectiles);
    updateCollision(enemy_projectiles);
    updateInvincibilityBlinking();
}

void Player::updateControl(sf::Time delta_time, std::vector<Projectile *> *player_projectiles) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.setPosition(std::max(sprite.getPosition().x - speed * (float) delta_time.asMilliseconds(), 0.0f),
                           sprite.getPosition().y);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.setPosition(
                std::min(sprite.getPosition().x + speed * (float) delta_time.asMilliseconds(),
                         1920.0f - (float) sprite.getTextureRect().getSize().x),
                sprite.getPosition().y);
    }


    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && reload_cooldown <= 0) {
        reload_cooldown = reload_time;
        // assumes that the projectile texture has a width of 16 pixels
        Projectile *projectile = new Projectile(-1.0f, sprite.getPosition().x +
                                                       (float) sprite.getTextureRect().getSize().y / 2 - 8,
                                                sprite.getPosition().y - 1, asset_manager);
        player_projectiles->push_back(projectile);
        asset_manager->getAudioManager()->playShootSFX();
    }
}

void Player::updateCollision(std::vector<Projectile *> *enemy_projectiles) {
    for (std::vector<Projectile *>::iterator iter = enemy_projectiles->begin();
         iter != enemy_projectiles->end(); iter++) {
        if ((*iter)->collidesWith(sprite.getGlobalBounds())) {
            if (invincibility_cooldown <= 0) {
                asset_manager->getAudioManager()->playHitSFX();
                game_state->lives--;
                invincibility_cooldown = invincibility_time;
            }
            delete *iter;
            enemy_projectiles->erase(iter);
            break;
        }
    }
    if (game_state->lives == 0) {
        asset_manager->getAudioManager()->playGameOverSFX();
        game_state->game_over = true;
    }
}

void Player::updateTimers(sf::Time delta_time) {
    invincibility_cooldown =
            invincibility_cooldown > delta_time.asMilliseconds() ? invincibility_cooldown - delta_time.asMilliseconds()
                                                                 : 0;
    invincibility_display_time = invincibility_display_time > delta_time.asMilliseconds() ? invincibility_display_time -
                                                                                            delta_time.asMilliseconds()
                                                                                          : 0;
    reload_cooldown = reload_cooldown > delta_time.asMilliseconds() ? reload_cooldown - delta_time.asMilliseconds() : 0;
}

void Player::updateInvincibilityBlinking() {
    if (invincibility_cooldown > 0) {
        if (invincibility_display_time <= 0) {
            invincibility_display_time = 200;
            display = !display;
        }
    } else {
        display = true;
    }
}
