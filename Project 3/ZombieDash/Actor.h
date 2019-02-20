#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

// Base class from which all actors will be derived
class Actor: public GraphObject {
public:
    // Constructor
    Actor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors
    bool isDead() const;
    bool overlaps(const Actor& other);
    StudentWorld* getWorld();

    // Mutators
    // Each actor can specify whether or not they can be killed (true/false)
    virtual bool setDead() = 0;

    // doSomething() to be called by move() function.
    // return false if the actor died
    virtual void doSomething() = 0;

protected:
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
    bool movesOnto(const Actor& other) const;

    // Mutators
    virtual bool infect() = 0;
    void increaseInfectedCount();
    virtual bool setDead();

protected:
    void setm_infected();

private:
    bool m_infected;
    int m_infectionCount;
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



class Penelope: public SentientActor {
public:
    // Constructor/Destructor
    Penelope(int startX, int startY, StudentWorld* world);

    // Accessors

    //Mutators
    virtual void doSomething();
    virtual bool infect();

private:
    int m_vaccines;
    int m_landmines;
    int m_flameCharges;
};



class Wall: public EnvironmentalActor {
public:
    // Constructor/Destructor
    Wall(int startX, int startY, StudentWorld* world);

    // Accessors

    // Mutators
    virtual void doSomething();
    virtual bool infect();
    virtual bool setDead();
private:

};

#endif // ACTOR_H_