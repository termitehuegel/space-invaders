#include <chrono>
#include <SFML/Graphics.hpp>


#include "header/assetManager.h"
#include "header/game.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Close);
    window.setFramerateLimit(144);
    sf::Clock clock;
    AssetManager* asset_manager = new AssetManager("assets");
    Game* game = new Game(asset_manager);

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
        game->update(delta_time);
        game->draw(&window);

        window.display();
    }
}

