#include <chrono>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>


#include "header/assetManager.h"
#include "header/game.h"
#include "header/menu.h"

/**
 * Tries to load the saved highscore from the file ./save.data.
 * @return the loaded highscore or 0.
 */
unsigned int loadHighscore() {
    unsigned int highscore = 0;
    std::ifstream save_file("save.data");
    std::string line;
    while (getline (save_file, line)) {
        int position = line.find("highscore=");
        if (position >= 0) {
            highscore = std::stoul(line.substr(position+10));
        }
    }
    save_file.close();
    return highscore;
}

/**
 * Saves the highscore to the file ./save.data and overrides the content of the save file in the process.
 * @param highscore that should be saved.
 */
void saveHighscore(unsigned int highscore) {
    std::ofstream save_file("save.data");
    save_file << "highscore=" << highscore;
    save_file.close();
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Default);
    window.setFramerateLimit(144);
    sf::Clock clock;
    AssetManager *asset_manager = new AssetManager("assets");
    Menu *menu = new Menu(asset_manager);
    Game *game = nullptr;
    unsigned int highscore = loadHighscore();

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
            if (game != nullptr && game->highscore() > highscore) {
                highscore = game->highscore();
                saveHighscore(highscore);
            }
            if (menu->update(delta_time, &window)) {
                delete game;
                game = new Game(asset_manager, highscore);
            }
            menu->draw(&window);
        }

        window.display();
    }
}

