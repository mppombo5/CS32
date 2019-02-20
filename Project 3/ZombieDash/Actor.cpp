#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

////////////////////////////
/// Actor Implementation ///
////////////////////////////

Actor::Actor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world)
: GraphObject(imageID, startX, startY, startDir, depth) {
    m_world = world;
    m_dead = false;
}

bool Actor::isDead() const {
    return m_dead;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

// This is just some circle math to decide if something overlaps
bool Actor::overlaps(const Actor& other) {
    double deltaX = other.getX() - getX();
    double deltaY = other.getY() - getY();

    return (deltaX * deltaX) + (deltaY * deltaY) <= 100;
}

void Actor::setm_dead() {
    m_dead = true;
}

////////////////////////////////////
/// SentientActor Implementation ///
////////////////////////////////////

SentientActor::SentientActor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world)
: Actor(imageID, startX, startY, startDir, depth, world) {
    m_infected = false;
    m_infectionCount = 0;
}

bool SentientActor::isInfected() const{
    return m_infected;
}

int SentientActor::infectedCount() const {
    return m_infectionCount;
}

void SentientActor::increaseInfectedCount() {
    m_infectionCount++;
}

bool SentientActor::movesOnto(const Actor& other) const {
    return false;
}

bool SentientActor::setDead() {
    if (!isDead()) {
        setm_dead();
        return true;
    }
    return false;
}

void SentientActor::setm_infected() {
    m_infected = true;
}

/////////////////////////////////////////
/// EnvironmentalActor Implementation ///
/////////////////////////////////////////

EnvironmentalActor::EnvironmentalActor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world)
: Actor(imageID, startX, startY, startDir, depth, world) {

}

///////////////////////////////
/// Penelope Implementation ///
///////////////////////////////

Penelope::Penelope(int startX, int startY, StudentWorld* world)
: SentientActor(IID_PLAYER, startX, startY, right, 0, world) {
    m_flameCharges = 0;
    m_landmines = 0;
    m_vaccines = 0;
}

void Penelope::doSomething() {
    if (isDead())
        return;
    if (isInfected())
        increaseInfectedCount();
    if (infectedCount() >= 500) {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_DIE);
        return;
    }
    int key;
    if (getWorld()->getKey(key)) {
        switch (key) {
            // do the things for each key
            case KEY_PRESS_RIGHT: {
                setDirection(right);
                double destX = getX() + 4;
                double destY = getY();
                // TODO: check if the destination would move onto anything
                moveTo(destX, destY);
                break;
            }
            case KEY_PRESS_DOWN: {
                setDirection(down);
                double destX = getX();
                double destY = getY() - 4;
                // TODO: check for blocking
                moveTo(destX, destY);
                break;
            }
            case KEY_PRESS_LEFT: {
                setDirection(left);
                double destX = getX() - 4;
                double destY = getY();
                // TODO: check for blocking
                moveTo(destX, destY);
                break;
            }
            case KEY_PRESS_UP: {
                setDirection(up);
                double destX = getX();
                double destY = getY() + 4;
                // TODO: check for blocking
                moveTo(destX, destY);
            }
            default:
                break;
        }
    }
}

bool Penelope::infect() {
    if (!isInfected()) {
        setm_infected();
        return true;
    }
    return false;
}

///////////////////////////
/// Wall Implementation ///
///////////////////////////

Wall::Wall(int startX, int startY, StudentWorld* world)
: EnvironmentalActor(IID_WALL, startX, startY, right, 0, world) {}

void Wall::doSomething() {}

bool Wall::infect() {
    return false;
}

bool Wall::setDead() {
    return false;
}


















