#include <algorithm>
#include <SFML/Graphics.hpp>

#include "header/projectile.h"
#include "header/player.h"

Player::Player(float speed, int reload_time) {
    this->speed = speed;
    texture.loadFromFile("assets/textures/player.png");
    sprite.setTexture(texture);
    sprite.setPosition(935, 1020);
    cooldown = 0;
    this->reload_time = reload_time;
}

void Player::draw(sf::RenderWindow *window) {
    window->draw(sprite);
}

void Player::update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles) {
    // CHECK IF HIT => remove life or game over

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.setPosition(std::max(sprite.getPosition().x - speed * delta_time.asMilliseconds(), 0.0f),
                           sprite.getPosition().y);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.setPosition(
                std::min(sprite.getPosition().x + speed * delta_time.asMilliseconds(), 1920.0f - texture.getSize().x),
                sprite.getPosition().y);
    }

    cooldown -= delta_time.asMilliseconds();
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && cooldown <= 0) {
        cooldown = reload_time;
        Projectile *projectile = new Projectile(-0.1f, sprite.getPosition().x + 4.5f,
                                                sprite.getPosition().y - 1);
        player_projectiles->push_back(projectile);
    }
}