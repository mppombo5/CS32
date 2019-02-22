#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

////////////////////////
/// Global Functions ///
////////////////////////

// checks whether num is contained in between lower and upper inclusive
bool containedIn(double num, double lower, double upper) {
    return (lower <= num && num <= upper);
}

bool intersectsBoundingBox(double destX, double destY, const Actor* actor) {
    // lower corners: destX,destY; otherX,otherY

    // checks:
    // otherX <= destX                 <= otherX+SPRITE_WIDTH-1  X
    // otherX <= destX+SPRITE_WIDTH-1 <= otherX+SPRITE_WIDTH-1   X
    // and
    // otherY <= destY                 <= otherY+SPRITE_HEIGHT-1 X
    // otherY <= destY+SPRITE_HEIGHT-1 <= otherY+SPRITE_HEIGHT-1 X

    double otherX     = actor->getX();
    double otherXEdge = actor->getX() + SPRITE_WIDTH-1;
    double otherY     = actor->getY();
    double otherYEdge = actor->getY() + SPRITE_HEIGHT-1;

    if ( ( containedIn(destX, otherX, otherXEdge) || containedIn(destX + SPRITE_WIDTH-1, otherX, otherXEdge))
       && (containedIn(destY, otherY, otherYEdge) || containedIn(destY + SPRITE_HEIGHT-1, otherY, otherYEdge)))
        return true;
    return false;
}

////////////////////////////
/// Actor Implementation ///
////////////////////////////

Actor::Actor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world)
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

bool Actor::blocked(double destX, double destY) const {
    list<Actor*> actorList = m_world->actorList();
    list<Actor*>::const_iterator it;

    for (it = actorList.begin(); it != actorList.end(); it++) {
        // check if each actor **would block** this one
        if ((*it)->wouldBlock(destX, destY, this)) {
            return true;
        }
    }
    // nothing returned true, so it's false
    return false;
}

bool Actor::wouldBlock(double destX, double destY, const Actor* actor) const {
    return false;
}

// simply makes it easier to make something move, as the check is built-in
void Actor::safeMoveTo(double destX, double destY) {
    if (!blocked(destX, destY))
        moveTo(destX, destY);
}

void Actor::setm_dead() {
    m_dead = true;
}

////////////////////////////////////
/// SentientActor Implementation ///
////////////////////////////////////

SentientActor::SentientActor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world)
        : Actor(imageID, startX, startY, startDir, depth, world) {
    m_infected = false;
    m_infectionCount = 0;
}

bool SentientActor::isInfected() const{
    return m_infected;
}

int SentientActor::infectionCount() const {
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

bool SentientActor::blockedOG(double destX, double destY, const std::list<Actor *> &actors) const {
    //return wouldBlock(destX, destY, getWorld()->actorList());
    return false;
}

bool SentientActor::wouldBlock(double destX, double destY, const Actor* actor) const {
    // IMPORTANT: make the actor parameter this, because this is the thing you're checking destX and destY against
    return intersectsBoundingBox(destX, destY, this);
}

void SentientActor::setm_infected() {
    m_infected = true;
}

///////////////////////////////
/// Penelope Implementation ///
///////////////////////////////

// Constructor/Destructor

Penelope::Penelope(double startX, double startY, StudentWorld* world)
        : SentientActor(IID_PLAYER, startX, startY, right, 0, world) {
    m_flames = 0;
    m_landmines = 0;
    m_vaccines = 0;
}

// Accessors

int Penelope::getVaccines() const {
    return m_vaccines;
}

int Penelope::getLandmines() const {
    return m_landmines;
}

int Penelope::getFlames() const {
    return m_flames;
}

// Mutators

void Penelope::doSomething() {
    // check if she's dead
    if (isDead())
        return;

    // check for infection, increase if she is and kill her if it reaches 500
    if (isInfected())
        increaseInfection();
    if (infectionCount() >= 500) {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_DIE);
        return;
    }

    // check for user input, respond appropriately
    int key;
    if (getWorld()->getKey(key)) {
        switch (key) {
            // directional key input
            case KEY_PRESS_RIGHT: {
                setDirection(right);
                double destX = getX() + 4;
                double destY = getY();
                safeMoveTo(destX, destY);
                break;
            }
            case KEY_PRESS_DOWN: {
                setDirection(down);
                double destX = getX();
                double destY = getY() - 4;
                safeMoveTo(destX, destY);
                break;
            }
            case KEY_PRESS_LEFT: {
                setDirection(left);
                double destX = getX() - 4;
                double destY = getY();
                safeMoveTo(destX, destY);
                break;
            }
            case KEY_PRESS_UP: {
                setDirection(up);
                double destX = getX();
                double destY = getY() + 4;
                safeMoveTo(destX, destY);
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

EnvironmentalActor::EnvironmentalActor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world)
        : Actor(imageID, startX, startY, startDir, depth, world) {

}

///////////////////////////
/// Wall Implementation ///
///////////////////////////

Wall::Wall(double startX, double startY, StudentWorld* world)
        : EnvironmentalActor(IID_WALL, startX, startY, right, 0, world) {}

void Wall::doSomething() {}

bool Wall::setDead() {
    return false;
}

bool Wall::wouldBlock(double destX, double destY, const Actor *actor) const {
    return (intersectsBoundingBox(destX, destY, this));
}

///////////////////////////
/// Exit Implementation ///
///////////////////////////

Exit::Exit(double startX, double startY, StudentWorld *world)
:EnvironmentalActor(IID_EXIT, startX, startY, right, 1, world) {

}

void Exit::doSomething() {

}



























