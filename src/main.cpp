#include <chrono>
#include <SFML/Graphics.hpp>


#include "header/assetManager.h"
#include "header/game.h"
#include "header/menu.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Default);
    window.setFramerateLimit(144);
    sf::Clock clock;
    AssetManager *asset_manager = new AssetManager("assets");
    Menu *menu = new Menu(asset_manager);
    Game *game = nullptr;

    /**
     * This is the update loop, that draws each frame and processes window events.
     */
    while (window.isOpen()) {
        sf::Time delta_time = clock.getElapsedTime();
        clock.restart();

        /**
         * Evaluate window events that happened. E.g. terminate if window is closed.
         */
        for (sf::Event event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
        }
        window.clear();

        if (game != nullptr && !game->gameOver()) {
            game->update(delta_time);
            game->draw(&window);
        } else {
            if (menu->update(delta_time, &window)) {
                delete game;
                game = new Game(asset_manager);
            }
            menu->draw(&window);
        }

        window.display();
    }
}

