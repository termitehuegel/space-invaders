#ifndef SPACE_INVADERS_ENEMY_H
#define SPACE_INVADERS_ENEMY_H


#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite sprite;
public:
    Enemy(sf::Texture* texture, float x, float y);
    void setPosition(float x, float y);
    sf::Vector2<float> getPosition();
    void draw(sf::RenderWindow *window);
};


#endif