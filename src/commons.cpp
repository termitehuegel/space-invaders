#include <fstream>
#include <string>

#include "../include/commons.h"

unsigned int loadHighscore()
{
    unsigned int highscore = 0;
    std::ifstream save_file("save.data");
    std::string line;
    while (getline(save_file, line))
    {
        int position = line.find("highscore=");
        if (position >= 0)
        {
            highscore = std::stoul(line.substr(position + 10));
        }
    }
    save_file.close();
    return highscore;
}

void saveHighscore(unsigned int highscore)
{
    std::ofstream save_file("save.data");
    save_file << "highscore=" << highscore;
    save_file.close();
}