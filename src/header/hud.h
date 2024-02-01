#ifndef SPACE_INVADERS_HUD_H
#define SPACE_INVADERS_HUD_H

#include "assetManager.h"
#include "gameState.h"

/**
 * The HUD class manages the heads up display.
 * It draws essential informations about the game state on the screen and informs the player about the
 * frame rate of the application.
 */
class HUD {
private:
    GameState *game_state;
    sf::Text *fps;
    sf::Text *score_text;
    sf::Text *score_number;
    sf::Text *highscore_text;
    sf::Text *highscore_number;
    sf::Text *lives_text;
    sf::Text *lives_number;
public:
    HUD(AssetManager *asset_manager, GameState *game_state);

    ~HUD();

    /**
     * This method draws the game state and the provided frame rate on screen.
     * @param window to be drawn to
     * @param fps the number of frames generated in one second
     */
    void draw(sf::RenderWindow *window, unsigned int fps);
};

#endif