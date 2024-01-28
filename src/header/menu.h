#ifndef SPACE_INVADERS_MENU_H
#define SPACE_INVADERS_MENU_H

#include <SFML/Graphics.hpp>
#include "assetManager.h"

/**
 * The Menu class is responsible to manage all menu behaviour.
 * More specifically it is responsible for drawing and managing the main menu and the options menu.
 */
class Menu {
private:
    /**
     * The MenuState enum specifies which state the menu can be in.
     * More specifically this specifies, which menus are available.
     */
    enum MenuState {
        MAIN,
        OPTIONS
    };

    /**
     * This Options struct hold all information that can be decided in the options menu.
     */
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

    sf::Sprite background;
    MenuState state;
    /**
     * The currently applied options.
     */
    Options options;
    /**
     * The options that are currently selected in the options menu.
     */
    Options selected_options;
    /**
     * The selected field specifies which option of the menu is currently selected.
     * The following values are expected:
     *
     * main menu:
     * 0 => play
     * 1 => options
     * 2 => quit
     *
     * options menu:
     * 0 => resolution
     * 1 => window mode
     * 2 => refresh rate
     * 3 => back
     * 4 => apply
     */
    unsigned char selected;
    int cooldown;

    /**
     * All texts that are part of the main menu.
     */
    sf::Text *play_text;
    sf::Text *options_text;
    sf::Text *quit_text;

    /**
     * All texts that are part of the options menu.
     */
    sf::Text *resolution_text;
    sf::Text *resolution_value_text;
    sf::Text *window_mode_text;
    sf::Text *window_mode_value_text;
    sf::Text *refresh_rate_text;
    sf::Text *refresh_rate_value_text;
    sf::Text *back_text;
    sf::Text *apply_text;

    /**
     * Applies the current options, that are saved in the options field to the provided window.
     * @param window that the options should be applied to
     */
    void applyOptions(sf::RenderWindow *window);

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

    /**
     * Draws the current state of the menu to the provided window.
     * @param window that the menu should be drawn to
     */
    void draw(sf::RenderWindow *window);
};

#endif
