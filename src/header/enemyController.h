#ifndef SPACE_INVADERS_ENEMYCONTROLLER_H
#define SPACE_INVADERS_ENEMYCONTROLLER_H

#include "enemy.h"

class EnemyController {
private:
    float speed;
    float acceleration;
    Enemy* enemies[11][5];
    sf::Texture textures[5];
    bool change_direction;
    float step;
public:
    EnemyController(float acceleration, float speed, float step);
    void update(sf::Time delta_time);
    void draw(sf::RenderWindow *window);
};


#endif