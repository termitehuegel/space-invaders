#include "../include/enemy.h"

Enemy::Enemy(sf::Texture* texture, float x, float y)
{
    sprite.setTexture(*texture);
    sprite.setPosition(x, y);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Enemy::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Enemy::draw(sf::RenderWindow* window) const
{
    window->draw(sprite);
}

sf::Vector2<float> Enemy::getPosition() const
{
    return sprite.getPosition();
}

bool Enemy::detectCollision(std::vector<Projectile*>* projectiles)
{
    for (std::vector<Projectile*>::iterator iter = projectiles->begin(); iter != projectiles->end(); iter++)
    {
        if ((*iter)->collidesWith(sprite.getGlobalBounds()))
        {
            delete *iter;
            projectiles->erase(iter);
            return true;
        }
    }
    return false;
}

Projectile* Enemy::shoot(AssetManager* asset_manager) const
{
    // assumes that the projectile texture has a width of 16 pixels
    return new Projectile(0.1f, sprite.getPosition().x + + static_cast<float>(sprite.getTextureRect().getSize().x) / 2.0f - 8.0f,
                          sprite.getPosition().y + static_cast<float>(sprite.getTextureRect().getSize().y + 1), asset_manager);
}

void Enemy::animationStep()
{
    // assumes that the texture of each animation step is 64x64 and there are 3 steps
    int x = (sprite.getTextureRect().getPosition().x + 64) % 192;
    sprite.setTextureRect(sf::IntRect(x, 0, 64, 64));
}
