#include "header/enemyController.h"

EnemyController::EnemyController(float acceleration, float speed, float step) {
    this->acceleration = acceleration;
    this->speed = speed;
    change_direction = false;
    this->step = step;

    textures[0].loadFromFile("assets/textures/enemy.png");

    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            enemies[x][y] = new Enemy(&textures[0], 150.0f + (float) x*125, 200.0f + (float) y*75.0f);
        }
    }
}

void EnemyController::update(sf::Time delta_time) {
    if (change_direction) {
        speed *= -1;
    }

    bool border_reached = false;
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            if (enemies[x][y] == nullptr) {
                continue;
            }
            sf::Vector2<float> position =  enemies[x][y]->getPosition();
            float new_x = position.x + speed * (float )delta_time.asMilliseconds();
            float new_y = position.y;
            if (change_direction) {
                new_y = position.y + step;
            }

            enemies[x][y]->setPosition(new_x, new_y);
            if (new_x <= 0 || new_x + (float) textures[0].getSize().x >= 1920) {
                border_reached = true;
            }
        }
    }
    if (change_direction) {
        change_direction = false;
    }
    if (border_reached) {
        change_direction = true;
    }

    //TODO: Shoot





}

void EnemyController::draw(sf::RenderWindow *window) {
    for (int x = 0; x < 11; x++) {
        for (int y = 0; y < 5; y++) {
            enemies[x][y]->draw(window);
        }
    }
}
