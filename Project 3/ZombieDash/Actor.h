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
    Actor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors
    virtual bool exits(const Actor* actor) const;
    virtual bool detectsExits() const;
    bool isDead() const;
    bool blocked(double destX, double destY) const;
    bool overlaps(const Actor* actor) const;
    StudentWorld* getWorld() const;

    // Mutators
      // Each actor can specify whether or not they can be killed (true/false)
    virtual void setDead();
    void safeMoveTo(double destX, double destY);

    // doSomething() to be called by move() function.
    // return false if the actor died
    virtual void doSomething() = 0;

protected:
    // Accessors
    virtual bool blocks(double destX, double destY, const Actor *actor) const;

    // Mutators
      // setDead() will be different for sentient and environmental actors, but I still need a way to set m_dead to false
    void setm_dead();

private:
    StudentWorld* m_world;
    bool m_dead;
};



///////////////////////
/// Sentient Actors ///
///////////////////////

// Actors that can move. For our purposes, zombies are indeed sentient.
class SentientActor: public Actor {
public:
    // Constructor/Destructor
    SentientActor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors
    virtual bool exits(const Actor* actor) const;
    bool isInfected() const;
    int infectionCount() const;

    // Mutators
    virtual void infect() = 0;
    virtual void setDead();
    void increaseInfection();

protected:
    // Accessors
    virtual bool blocks(double destX, double destY, const Actor *actor) const;

    // Mutators
    void setm_infected();

private:
    bool m_infected;
    int m_infectionCount;
};



class Penelope: public SentientActor {
public:
    // Constructor/Destructor
    Penelope(double startX, double startY, StudentWorld* world);

    // Accessors
    int getVaccines() const;
    int getLandmines() const;
    int getFlames() const;

    // Mutators
    virtual void doSomething();
    virtual void infect();

private:
    int m_vaccines;
    int m_landmines;
    int m_flames;
};



class Zombie: public SentientActor {
public:
    // Constructor/Destructor

    // Accessors
    virtual bool exits(const Actor* actor) const;

    // Mutators

private:

};



////////////////////////////
/// Environmental Actors ///
////////////////////////////

// Actors that do not move – e.g. walls, mines, flames, vomit, etc.
class EnvironmentalActor: public Actor {
public:
    // Constructor/Destructor
    EnvironmentalActor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world);

    // Accessors

    // Mutators

protected:
    // Accessors

    // Mutators

private:

};



class Wall: public EnvironmentalActor {
public:
    // Constructor/Destructor
    Wall(double startX, double startY, StudentWorld* world);

    // Accessors

    // Mutators
    virtual void doSomething();

protected:
    // Accessors
    virtual bool blocks(double destX, double destY, const Actor *actor) const;

    // Mutators

private:

};



class Exit: public EnvironmentalActor {
public:
    // Constructor/Destructor
    Exit(double startX, double startY, StudentWorld* world);

    // Accessors
    virtual bool detectsExits() const;
    bool citExits() const;
    bool playerExits() const;

    // Mutators
    virtual void doSomething();

protected:
    // Accessors

    // Mutators

private:

};



class Pit: public EnvironmentalActor {
public:
    // Constructor/Destructor
    Pit(double startX, double startY, StudentWorld* world);

    // Accessors

    // Mutators

private:

};

#endif // ACTOR_H_




























