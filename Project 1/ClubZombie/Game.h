//
// Created by Matthew Pombo on 2019-01-10.
//

#ifndef CLUBZOMBIE_GAME_H
#define CLUBZOMBIE_GAME_H

#include "Arena.h"

int decodeDirection(char dir);

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();

    // Mutators
    void play();

private:
    Arena* m_arena;
};


#endif //CLUBZOMBIE_GAME_H
