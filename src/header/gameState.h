#ifndef SPACE_INVADERS_GAMESTATE_H
#define SPACE_INVADERS_GAMESTATE_H

struct GameState {
    bool game_over;
    unsigned int score;
    unsigned int highscore;
    unsigned int lives;
};

#endif
