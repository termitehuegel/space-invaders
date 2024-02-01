#ifndef SPACE_INVADERS_BASEFRAGMENT_H
#define SPACE_INVADERS_BASEFRAGMENT_H

#include <SFML/Graphics.hpp>
#include "projectile.h"

class BaseFragment {
public:
    BaseFragment(sf::Texture *texture, float x, float y);

    bool detectCollision(std::vector<Projectile*>* enemy_projectiles, std::vector<Projectile*>* player_projectiles);

    void draw(sf::RenderWindow *window);
private:
    sf::Sprite sprite;
};

#endif