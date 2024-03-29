#include <SFML/Graphics.hpp>

#include "../include/projectile.h"

Projectile::Projectile(float speed, float x, float y, AssetManager* asset_manager)
{
    this->speed = speed;
    sprite.setTexture(*asset_manager->getTextures()->at("projectile"));
    sprite.setPosition(x, y);
    if (sprite.getGlobalBounds().intersects({0, 0, 1920, 1080}))
    {
        in_bound = true;
    }
}

void Projectile::draw(sf::RenderWindow* window) const
{
    window->draw(sprite);
}

void Projectile::update(sf::Time delta_time)
{
    float new_y = sprite.getPosition().y + speed * static_cast<float>(delta_time.asMilliseconds());
    if (new_y < static_cast<float>(-sprite.getTextureRect().getSize().y) || new_y > 1080)
    {
        in_bound = false;
    }
    sprite.setPosition(sprite.getPosition().x, new_y);
}

bool Projectile::isInBound() const
{
    return in_bound;
}

bool Projectile::collidesWith(sf::FloatRect bounds) const
{
    return sprite.getGlobalBounds().intersects(bounds);
}

sf::Rect<float> Projectile::getBounds() const
{
    return sprite.getGlobalBounds();
}