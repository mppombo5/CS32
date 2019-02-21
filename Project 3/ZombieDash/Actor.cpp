#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/////////////////////////////////////////
/// Global Functions, to be used ////////
/// when two non-connected classes //////
/// need to do the same thing ///////////
/////////////////////////////////////////

// this might end up being empty lmao

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

StudentWorld* Actor::getWorld() const {
    return m_world;
}

// This is just some circle math to decide if something overlaps
// TODO: probably need to iterate through m_actors
bool Actor::overlaps(const Actor& other) const {
    double srcXCenter = (getX() + SPRITE_WIDTH) / 2;
    double srcYCenter = (getY() + SPRITE_HEIGHT) / 2;
    double otherXCenter = (other.getX() + SPRITE_WIDTH) / 2;
    double otherYCenter = (other.getY() + SPRITE_HEIGHT) / 2;

    double deltaX = otherXCenter - srcXCenter;
    double deltaY = otherYCenter - srcYCenter;

    return (deltaX * deltaX) + (deltaY * deltaY) <= 100;
}

// check if the destination of an actor would block the
bool Actor::blocked(double destX, double destY, const std::list<Actor*>& actors) const {
    return false;
}

bool Actor::wouldBlock(double destX, double destY, const list<Actor*>& actors) const {
    // lower corners: destX,destY; otherX,otherY

    // checks:
    // otherX <= destX                 <= otherX+SPRITE_WIDTH-1  X
    // otherX <= destX+SPRITE_WIDTH-1 <= otherX+SPRITE_WIDTH-1   X
    // and
    // otherY <= destY                 <= otherY+SPRITE_HEIGHT-1 X
    // otherY <= destY+SPRITE_HEIGHT-1 <= otherY+SPRITE_HEIGHT-1 X

    // implement the for loop for m_actors here
    list<Actor*>::const_iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        if (   (((*it)->getX() <= destX                    && destX                    <= (*it)->getX() + SPRITE_WIDTH-1)
                ||  ((*it)->getX() <= destX + SPRITE_WIDTH-1   && destX + SPRITE_WIDTH-1   <= (*it)->getX() + SPRITE_WIDTH-1))
               && (((*it)->getY() <= destY                    && destY                    <= (*it)->getY() + SPRITE_HEIGHT-1)
                   ||  ((*it)->getY() <= destY + SPRITE_HEIGHT-1  && destY + SPRITE_HEIGHT-1  <= (*it)->getY() + SPRITE_HEIGHT-1)))
            return true;
    }
    return false;
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

void SentientActor::increaseInfection() {
    m_infectionCount++;
}

bool SentientActor::setDead() {
    if (!isDead()) {
        setm_dead();
        return true;
    }
    return false;
}

bool SentientActor::blocked(double destX, double destY, const std::list<Actor*>& actors) const {
    return wouldBlock(destX, destY, getWorld()->actorList());
}

void SentientActor::setm_infected() {
    m_infected = true;
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
        increaseInfection();
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
                if (!blocked(destX, destY, getWorld()->actorList()))
                    moveTo(destX, destY);
                break;
            }
            case KEY_PRESS_DOWN: {
                setDirection(down);
                double destX = getX();
                double destY = getY() - 4;
                if (!blocked(destX, destY, getWorld()->actorList()))
                    moveTo(destX, destY);
                break;
            }
            case KEY_PRESS_LEFT: {
                setDirection(left);
                double destX = getX() - 4;
                double destY = getY();
                if (!blocked(destX, destY, getWorld()->actorList()))
                    moveTo(destX, destY);
                break;
            }
            case KEY_PRESS_UP: {
                setDirection(up);
                double destX = getX();
                double destY = getY() + 4;
                if (!blocked(destX, destY, getWorld()->actorList()))
                    moveTo(destX, destY);
                break;
            }
            default:
                break;
        }
    }
}

void Penelope::infect() {
    if (!isInfected())
        setm_infected();
}

/////////////////////////////////////////
/// EnvironmentalActor Implementation ///
/////////////////////////////////////////

EnvironmentalActor::EnvironmentalActor(int imageID, int startX, int startY, Direction startDir, int depth, StudentWorld* world)
        : Actor(imageID, startX, startY, startDir, depth, world) {

}

///////////////////////////
/// Wall Implementation ///
///////////////////////////

Wall::Wall(int startX, int startY, StudentWorld* world)
        : EnvironmentalActor(IID_WALL, startX, startY, right, 0, world) {}

void Wall::doSomething() {}

bool Wall::setDead() {
    return false;
}



























