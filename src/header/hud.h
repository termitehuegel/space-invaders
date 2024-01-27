#ifndef SPACE_INVADERS_HUD_H
#define SPACE_INVADERS_HUD_H

#include "assetManager.h"
#include "gameState.h"

class HUD {
private:
    GameState *game_state;
    sf::Text *score_text;
    sf::Text *score_number;
    sf::Text *highscore_text;
    sf::Text *highscore_number;
    sf::Text *lives_text;
    sf::Text *lives_number;
public:
    HUD(AssetManager *asset_manager, GameState *game_state);

    void draw(sf::RenderWindow *window);
};

#endif