#include "header/enemy.h"

Enemy::Enemy(sf::Texture* texture, float x, float y) {;
    sprite.setTexture(*texture);
    sprite.setPosition(x, y);
}

void Enemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Enemy::draw(sf::RenderWindow *window) {
    window->draw(sprite);
}

sf::Vector2<float> Enemy::getPosition() {
    return sprite.getPosition();
}
