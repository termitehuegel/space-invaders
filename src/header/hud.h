#ifndef SPACE_INVADERS_HUD_H
#define SPACE_INVADERS_HUD_H

class HUD {
private:
    sf::Font font_cour;
    sf::Text *score_text;
    sf::Text *score_number;
    sf::Text *highscore_text;
    sf::Text *highscore_number;
    sf::Text *lives_text;
    sf::Text *lives_number;
public:
    HUD();
    void draw(sf::RenderWindow *window, unsigned int score, unsigned int highscore, unsigned int lives);
};

#endif