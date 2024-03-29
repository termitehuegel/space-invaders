#include "../include/commons.h"
#include "../include/baseFragment.h"

BaseFragment::BaseFragment(sf::Texture* texture, float x, float y)
{
    sprite.setTexture(*texture);
    sprite.setPosition(x, y);
}

bool BaseFragment::detectCollision(std::vector<Projectile*>* enemy_projectiles,
                                   std::vector<Projectile*>* player_projectiles)
{
    for (std::vector<Projectile*>::iterator iter = enemy_projectiles->begin();
         iter != enemy_projectiles->end(); iter++)
    {
        if ((*iter)->collidesWith(sprite.getGlobalBounds()))
        {
            saveDelete(*iter);
            enemy_projectiles->erase(iter);
            return true;
        }
    }
    for (std::vector<Projectile*>::iterator iter = player_projectiles->begin();
         iter != player_projectiles->end(); iter++)
    {
        if ((*iter)->collidesWith(sprite.getGlobalBounds()))
        {
            saveDelete(*iter);
            player_projectiles->erase(iter);
            return true;
        }
    }
    return false;
}

void BaseFragment::draw(sf::RenderWindow* window) const
{
    window->draw(sprite);
}