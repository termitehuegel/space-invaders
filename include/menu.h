#ifndef SPACE_INVADERS_MENU_H
#define SPACE_INVADERS_MENU_H

#include "SFML/Graphics.hpp"
#include "assetManager.h"

/**
 * The Menu class is responsible to manage all menu behaviour.
 * More specifically it is responsible for drawing and managing the main menu and the options menu.
 */
class Menu {
public:
    Menu(AssetManager *asset_manager);

    ~Menu();

    bool update(sf::Time delta_time, sf::RenderWindow *window);

    void draw(sf::RenderWindow *window);

private:
    AssetManager *asset_manager;
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
        float music_volume;
        float sfx_volume;
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
     * 3 => music volume
     * 4 => sfx volume
     * 5 => back
     * 6 => apply
     */
    unsigned char selected;
    /**
     * interaction cooldown to avoid unintentional double inputs
     */
    unsigned int cooldown;

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
    sf::Text *music_volume_text;
    sf::Text *music_volume_value_text;
    sf::Text *sfx_volume_text;
    sf::Text *sfx_volume_value_text;
    sf::Text *back_text;
    sf::Text *apply_text;

    /**
     * Applies the current options, that are saved in the options field to the provided window and the saved assert manager.
     * @param window that the options should be applied to
     */
    void applyOptions(sf::RenderWindow *window);

    /**
     * Reduces all cooldowns
     */
    void updateTimers(sf::Time delta_time);

    void updateMainMenuSelection();

    bool updateMainMenuExecution();

    void updateOptionsMenuSelection();

    void updateOptionsMenuExecution(sf::RenderWindow *window);

    /**
     * @return true if a new game should be started and false otherwise
     */
    bool updateMainMenu();

    void updateOptionsMenu(sf::RenderWindow *window);

    void drawMainMenu(sf::RenderWindow *window);

    void drawOptionsMenu(sf::RenderWindow *window);
};

#endif