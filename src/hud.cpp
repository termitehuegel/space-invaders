#include <string>
#include <SFML/Graphics.hpp>

#include "header/hud.h"

HUD::HUD(AssetManager* asset_manager, GameState* game_state) {
    this->game_state = game_state;

    sf::Font* cour = asset_manager->getFonts()->at("cour");

    fps = new sf::Text("FPS:10", *cour, 15);
    score_text = new sf::Text("SCORE", *cour, 50);
    highscore_text = new sf::Text("HIGHSCORE", *cour, 50);
    lives_text = new sf::Text("LIVES", *cour, 50);
    score_number = new sf::Text("00000", *cour, 50);
    highscore_number = new sf::Text("00000", *cour, 50);
    lives_number = new sf::Text("0", *cour, 50);

    fps->setFillColor(sf::Color(200, 200, 200, 200));
    score_text->setFillColor(sf::Color::White);
    highscore_text->setFillColor(sf::Color::White);
    lives_text->setFillColor(sf::Color::White);

    score_number->setFillColor(sf::Color::Green);
    highscore_number->setFillColor(sf::Color::Green);
    lives_number->setFillColor(sf::Color::Green);

    fps->setPosition(2, 2);
    score_text->setPosition(25, 25);
    score_number->setPosition(25, 75);

    lives_text->setPosition(800, 25);
    lives_number->setPosition(860, 75);

    highscore_text->setPosition(1600, 25);
    highscore_number->setPosition(1600, 75);
}

void HUD::draw(sf::RenderWindow *window, unsigned int fps) {
    std::string score_string = std::to_string(game_state->score);
    std::string highscore_string = std::to_string(game_state->highscore);

    if (score_string.length() < 5) {
        score_string.insert(0, 5 - score_string.length(), '0');
    }

    if (highscore_string.length() < 5) {
        highscore_string.insert(0, 5 - highscore_string.length(), '0');
    }

    this->fps->setString("FPS:" + std::to_string(fps));
    score_number->setString(score_string);
    highscore_number->setString(highscore_string);
    lives_number->setString(std::to_string(game_state->lives));

    window->draw(*this->fps);
    window->draw(*score_text);
    window->draw(*highscore_text);
    window->draw(*lives_text);
    window->draw(*score_number);
    window->draw(*highscore_number);
    window->draw(*lives_number);
}