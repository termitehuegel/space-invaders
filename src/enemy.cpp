#include "../include/enemy.h"

Enemy::Enemy(sf::Texture *texture, float x, float y) {
    sprite.setTexture(*texture);
    sprite.setPosition(x, y);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
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

bool Enemy::detectCollision(std::vector<Projectile *> *projectiles) {
    for (std::vector<Projectile *>::iterator iter = projectiles->begin(); iter != projectiles->end(); iter++) {
        if ((*iter)->collidesWith(sprite.getGlobalBounds())) {
            delete *iter;
            projectiles->erase(iter);
            return true;
        }
    }
    return false;
}

Projectile *Enemy::shoot(AssetManager *asset_manager) {
    return new Projectile(0.1f, sprite.getPosition().x + sprite.getTextureRect().getSize().x / 2 - 8,
                          sprite.getPosition().y + sprite.getTextureRect().getSize().y + 1, asset_manager);
}

void Enemy::animationStep() {
    int x = (sprite.getTextureRect().getPosition().x + 64) % 192;
    sprite.setTextureRect(sf::IntRect(x, 0, 64, 64));
}
