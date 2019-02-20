#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Penelope;

class StudentWorld : public GameWorld
{
public:
    // Constructor/Destructor
    StudentWorld(std::string assetPath);

    // Mutators
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void levelExample();

private:
    // I chose a list because it automatically removes any deleted objects instead of having to step over deleted ones.
    // It's possible that a vector works the same way... I'm not sure. I need to study.
    std::list<Actor*> m_actors;
    Penelope* m_player;

    // keeps track of how many citizens are left in the level
    int m_citsLeft;
};

#endif // STUDENTWORLD_H_
