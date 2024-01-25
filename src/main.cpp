#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "header/projectile.h"
#include "header/hud.h"
#include "header/player.h"

struct GameState {
    bool game_over;
    unsigned int score;
    unsigned int highscore;
    unsigned int lives;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Close);
    window.setFramerateLimit(144);

    sf::Sprite background;
    sf::Texture background_texture;

    background_texture.loadFromFile("assets/textures/background.png");
    background.setTexture(background_texture);

    HUD *hud = new HUD();
    sf::Clock clock;
    GameState game_state = {false, 0, 0, 3};
    std::vector<Projectile*> player_projectiles = {};

    Player* player = new Player(0.5f, 2500);

    while (window.isOpen()) {
        sf::Time delta_time = clock.getElapsedTime();
        clock.restart();

        for (sf::Event event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }
        window.clear();

        player->update(delta_time, &player_projectiles);
        for (std::vector<Projectile*>::iterator iterator = player_projectiles.begin(); iterator != player_projectiles.end();) {
            (*iterator)->update(delta_time);
            if (!(*iterator)->isInBound()) {
                delete *iterator;
                iterator = player_projectiles.erase(iterator);
                std::cout << "deleted";
            } else {
                iterator++;
            }
        }

        window.draw(background);
        hud->draw(&window, game_state.score, game_state.highscore, game_state.lives);
        player->draw(&window);
        for (Projectile* projectile : player_projectiles) {
            projectile->draw(&window);
        }

        window.display();
    }
}

