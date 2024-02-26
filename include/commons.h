#ifndef SPACE_INVADERS_COMMONS_H
#define SPACE_INVADERS_COMMONS_H

/**
 * Tries to load the saved highscore from the file ./save.data.
 * @return the loaded highscore or 0.
 */
unsigned int loadHighscore();

/**
 * Saves the highscore to the file ./save.data and overrides the content of the save file in the process.
 * @param highscore that should be saved.
 */
void saveHighscore(unsigned int highscore);

/**
 * Deallocates memory associated with pointer in a save way (null safety).
 */
template<typename T>
void saveDelete(T*& ptr)
{
    // Implementation must be part of the header otherwise a linker error will be caused.
    if (ptr != nullptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

#endif
