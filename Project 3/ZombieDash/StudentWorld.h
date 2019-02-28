#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Human;
class Penelope;
class Zombie;

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
    void addActor(Actor* a);
    void decCitsLeft();
    void setFinished();
    void killActorsInPits(const Actor* killer);
    void killBurnedActors(const Actor* killer);
    void infectOverlappingActors(const Actor* killer);

    // Accessors
    Penelope* getPlayer() const;
    Human* getClosestPersonToZombie(const Zombie* zombie) const;
    int citsLeft() const;
      // always pass in "this" to hasActorBlockingMovement, so it won't compare against itself
    bool hasActorBlockingMovement(double destX, double destY, const Actor* checker) const;
    bool playerBlocksMovement(double destX, double destY) const;
    bool hasActorBlockingFlames(double destX, double destY) const;
    bool actorWouldOverlap(double destX, double destY) const;
    bool actorWouldGetPukedOn(double destX, double destY) const;
    bool actorTriggersLandmine(const Actor* checker) const;

private:
    // I chose a list because it automatically removes any deleted objects instead of having to step over deleted ones.
    // It's possible that a vector works the same way... I'm not sure. I need to study.
    std::list<Actor*> m_actors;
    Penelope* m_player;

    // keeps track of how many citizens are left in the level
    int m_citsLeft;

    // whether or not the level should be marked as finished
    bool m_levelFinished;
    // this is a debug counter so I can have events happen at specific times, mostly to check
    // actor interaction when spawning in the same location
    int m_debugTicks;
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











