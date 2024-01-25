#include <SFML/Graphics.hpp>

#include "header/projectile.h"

Projectile::Projectile(float speed, float x, float y) {
    this->speed = speed;
    texture.loadFromFile("assets/textures/projectile.png");
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    if (sprite.getGlobalBounds().intersects({0, 0, 1920,180})) {
        in_bound = true;
    }
}

void Projectile::draw(sf::RenderWindow *window) {
    window->draw(sprite);
}

void Projectile::update(sf::Time delta_time) {
    float new_y = sprite.getPosition().y + speed * delta_time.asMilliseconds();
    if (new_y < -((float) texture.getSize().y) || new_y > 1080) {
        in_bound = false;
    }
    sprite.setPosition(sprite.getPosition().x, new_y);
}

float Projectile::getSpeed() {
    return speed;
}

bool Projectile::isInBound() {
    return in_bound;
}
