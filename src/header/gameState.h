#ifndef SPACE_INVADERS_GAMESTATE_H
#define SPACE_INVADERS_GAMESTATE_H

/**
 * The GameState struct holds necessary information about the game state.
 * How many lives are left?
 * Has the player lost?
 * What is the current score?
 * What is the highscore;
 */
struct GameState {
    bool game_over;
    unsigned int score;
    unsigned int highscore;
    unsigned int lives;
};

#endif
