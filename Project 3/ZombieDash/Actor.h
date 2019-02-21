#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <list>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

// Base class from which all actors will be derived
class Actor: public GraphObject {
public:
    // Constructor
    Actor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors
    bool isDead() const;
    bool overlaps(const Actor& other) const;
    virtual bool blocked(double destX, double destY, const std::list<Actor*>& actors) const;
    StudentWorld* getWorld() const;


    // Mutators
    // Each actor can specify whether or not they can be killed (true/false)
    virtual bool setDead() = 0;

    // doSomething() to be called by move() function.
    // return false if the actor died
    virtual void doSomething() = 0;

protected:
    // Member functions
    bool wouldBlock(double destX, double destY, const std::list<Actor*>& actors) const;

    // Data members

    // setDead() will be different for sentient and environmental actors, but I still need a way to set
    // m_dead to false
    void setm_dead();

private:
    StudentWorld* m_world;
    bool m_dead;
};



// Actors that can move. For our purposes, zombies are indeed sentient.
class SentientActor: public Actor {
public:
    // Constructor/Destructor
    SentientActor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors
    bool isInfected() const;
    int infectedCount() const;
    virtual bool blocked(double destX, double destY, const std::list<Actor*>& actors) const;

    // Mutators
    virtual void infect() = 0;
    void increaseInfection();
    virtual bool setDead();

protected:
    void setm_infected();

private:
    bool m_infected;
    int m_infectionCount;
};



class Penelope: public SentientActor {
public:
    // Constructor/Destructor
    Penelope(int startX, int startY, StudentWorld* world);

    // Accessors

    //Mutators
    virtual void doSomething();
    virtual void infect();

private:
    int m_vaccines;
    int m_landmines;
    int m_flameCharges;
};



// Actors that do not move – e.g. walls, mines, flames, vomit, etc.
class EnvironmentalActor: public Actor {
public:
    // Constructor/Destructor
    EnvironmentalActor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors

    // Mutators
private:

};



class Wall: public EnvironmentalActor {
public:
    // Constructor/Destructor
    Wall(int startX, int startY, StudentWorld* world);

    // Accessors

    // Mutators
    virtual void doSomething();
    virtual bool setDead();
private:

};

#endif // ACTOR_H_