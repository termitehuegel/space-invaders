#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    int cooldown;
    int reload_time;
public:
    Player(float speed, int reload_time);
    void draw(sf::RenderWindow *window);
    void update(sf::Time delta_time, std::vector<Projectile *> *player_projectiles);
};

#endif