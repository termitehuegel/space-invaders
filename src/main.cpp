#include <SFML/Graphics.hpp>

#include "../include/commons.h"
#include "../include/assetManager.h"
#include "../include/game.h"
#include "../include/menu.h"

int main()
{
    /**
     * The Game is developed for 1920x1080 and is then scaled to the specified size.
     */
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Default);
    sf::Clock clock;
    AssetManager* asset_manager = new AssetManager("assets");
    Menu* menu = new Menu(asset_manager);
    Game* game = nullptr;
    unsigned int highscore = loadHighscore();
    window->setFramerateLimit(144);
    window->setIcon(asset_manager->getImages()->at("icon")->getSize().y,
                   asset_manager->getImages()->at("icon")->getSize().y,
                   asset_manager->getImages()->at("icon")->getPixelsPtr());

    // This is the window loop, that draws each frame and processes window events.
    while (window->isOpen())
    {
        sf::Time delta_time = clock.getElapsedTime();
        clock.restart();

        // Evaluate window events that happened. E.g. terminate if window is closed.
        for (sf::Event event = sf::Event{}; window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                saveDelete(window);
                saveDelete(game);
                saveDelete(menu);
                saveDelete(asset_manager);
                return EXIT_SUCCESS;
            }
        }
        window->clear();

        if (game != nullptr && !game->gameOver())
        {
            game->update(delta_time);
            game->draw(window);
        } else
        {
            if (game != nullptr && game->highscore() > highscore)
            {
                highscore = game->highscore();
                saveHighscore(highscore);
            }
            saveDelete(game);
            Menu::Action menu_action = menu->update(delta_time, window);
            if (menu_action == Menu::QUIT) {
                break;
            }
            if (menu_action == Menu::START_GAME) {
                game = new Game(asset_manager, highscore, 1500);
            }
            menu->draw(window);
        }

        window->display();
    }

    saveDelete(window);
    saveDelete(game);
    saveDelete(menu);
    saveDelete(asset_manager);
    return EXIT_SUCCESS;
}