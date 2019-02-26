#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Penelope;

class StudentWorld: public GameWorld
{
public:
    // Constructor/Destructor
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();

    // Mutators
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void decCitsLeft();
    void setFinished();
      // secondaryCondition is the condition that must be true to kill the actors
      // e.g. damagedByFlame, fallsIntoPits
    void killOverlappingActors(const Actor* killer, bool targetActorsCondition);
    void infectOverlappingActors(const Actor* killer);

    // Accessors
    Penelope* getPlayer() const;
    int citsLeft() const;
    bool hasBlockingActor(double destX, double destY, const Actor* actor) const;

private:
    // I chose a list because it automatically removes any deleted objects instead of having to step over deleted ones.
    // It's possible that a vector works the same way... I'm not sure. I need to study.
    std::list<Actor*> m_actors;
    Penelope* m_player;

    // keeps track of how many citizens are left in the level
    int m_citsLeft;

    // whether or not the level should be marked as finished
    bool m_levelFinished;
};



/// Inline Declarations ///

inline
StudentWorld::StudentWorld(std::string assetPath)
: GameWorld(assetPath) {}

inline
StudentWorld::~StudentWorld() {
    cleanUp();
}

inline
Penelope* StudentWorld::getPlayer() const {
    return m_player;
}

inline
int StudentWorld::citsLeft() const {
    return m_citsLeft;
}

inline
void StudentWorld::decCitsLeft() {
    if (m_citsLeft > 0)
        m_citsLeft--;
}

// only to be called by the Exit class when the player has completed the level
inline
void StudentWorld::setFinished() {
    if (!m_levelFinished)
        m_levelFinished = true;
}

#endif // STUDENTWORLD_H_











