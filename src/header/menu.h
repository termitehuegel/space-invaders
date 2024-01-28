#ifndef SPACE_INVADERS_MENU_H
#define SPACE_INVADERS_MENU_H

#include <SFML/Graphics.hpp>
#include "assetManager.h"

class Menu {
private:
    enum MenuState {
        MAIN,
        OPTIONS
    };

    struct Options {
        enum Resolution {
            QUARTER_HD,
            HD,
            FULL_HD,
            WQHD
        };

        enum WindowMode {
            WINDOWED,
            BORDERLESS,
        };

        enum RefreshRate {
            THIRTY_HERTZ,
            SIXTY_HERTZ,
            HUNDRED_FORTY_FOUR_HERTZ
        };

        Resolution resolution;
        WindowMode window_mode;
        RefreshRate refresh_rate;
    };

    MenuState state;
    Options options;
    Options selected_options;
    unsigned int selected;
    int cooldown;


    sf::Text *play_text;
    sf::Text *options_text;
    sf::Text *quit_text;

    sf::Text *resolution_text;
    sf::Text *resolution_value_text;
    sf::Text *window_mode_text;
    sf::Text *window_mode_value_text;
    sf::Text *refresh_rate_text;
    sf::Text *refresh_rate_value_text;
    sf::Text *back_text;
    sf::Text *apply_text;


    void applyOptions(sf::RenderWindow* window);

    void updateMainMenuSelection();

    bool updateMainMenuExecution();

    void updateOptionsMenuSelection();

    void updateOptionsMenuExecution(sf::RenderWindow *window);

    bool updateMainMenu(sf::Time delta_time);

    void updateOptionsMenu(sf::Time delta_time, sf::RenderWindow *window);

    void drawMainMenu(sf::RenderWindow *window);

    void drawOptionsMenu(sf::RenderWindow *window);

public:
    Menu(AssetManager *asset_manager);

    bool update(sf::Time delta_time, sf::RenderWindow *window);

    void draw(sf::RenderWindow *window);
};

#endif
