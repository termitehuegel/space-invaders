#ifndef SPACE_INVADERS_PROJECTILE_H
#define SPACE_INVADERS_PROJECTILE_H


class Projectile {
private:
    float speed;
    sf::Texture texture;
    sf::Sprite sprite;
    bool in_bound;
public:
    Projectile(float speed, float x, float y);

    void draw(sf::RenderWindow *window);

    void update(sf::Time delta_time);

    float getSpeed();

    bool isInBound();
};

#endif