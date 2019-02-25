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

bool intersectsBoundingBox(double destX, double destY, const Actor* otherActor) {
    // lower corners: destX,destY; otherX,otherY

    // checks:
    // otherX <= destX                 <= otherX+SPRITE_WIDTH-1
    // otherX <= destX+SPRITE_WIDTH-1 <= otherX+SPRITE_WIDTH-1
    // and
    // otherY <= destY                 <= otherY+SPRITE_HEIGHT-1
    // otherY <= destY+SPRITE_HEIGHT-1 <= otherY+SPRITE_HEIGHT-1

    double otherX     = otherActor->getX();
    double otherXEdge = otherActor->getX() + SPRITE_WIDTH-1;
    double otherY     = otherActor->getY();
    double otherYEdge = otherActor->getY() + SPRITE_HEIGHT-1;

    if (  (containedIn(destX, otherX, otherXEdge) || containedIn(destX + SPRITE_WIDTH-1, otherX, otherXEdge))
       && (containedIn(destY, otherY, otherYEdge) || containedIn(destY + SPRITE_HEIGHT-1, otherY, otherYEdge)))
        return true;
    return false;
}

////////////////////////////
/// Actor Implementation ///
////////////////////////////

/// Constructor/Destructor ///

Actor::Actor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world)
        : GraphObject(imageID, startX, startY, startDir, depth) {
    m_world = world;
    m_dead = false;
}

/// Accessors ///

bool Actor::exits(const Actor* actor) const {
    return false;
    // for actors that can exit, just check if they're overlapping
}

// only the Exit class will ever return true, but so be it
bool Actor::detectsExits() const {
    return false;
}

bool Actor::isDead() const {
    return m_dead;
}

bool Actor::blocks(double destX, double destY, const Actor *actor) const {
    return false;
}

// Important distinction:
// "blocked" checks whether or not the actor *is blocked* by any of StudentWorld's actors
// "blocks" means it blocks the movement of an actor to a destination
bool Actor::blocked(double destX, double destY) const {
    list<Actor*> actorList = m_world->actorList();
    list<Actor*>::const_iterator it;

    for (it = actorList.begin(); it != actorList.end(); it++) {
        // check if each actor **would block** this one
        if ((*it)->blocks(destX, destY, this)) {
            return true;
        }
    }
    // nothing returned true, so it's false
    return false;
}

bool Actor::overlaps(const Actor* other) const {
    // "XC" and "YC" mean "XCenter" and "YCenter"
    double srcXC = (getX() + SPRITE_WIDTH) / 2;
    double srcYC = (getY() + SPRITE_HEIGHT) / 2;
    double otherXC = (other->getX() + SPRITE_WIDTH) / 2;
    double otherYC = (other->getY() + SPRITE_HEIGHT) / 2;

    // "dX" means delta(X)
    double dX = otherXC - srcXC;
    double dY = otherYC - srcYC;

    return (dX * dX) + (dY * dY) <= 100;
}

StudentWorld* Actor::getWorld() const {
    return m_world;
}

/// Mutators ///

// By default, things shouldn't die unless explicitly defined that they can
void Actor::setDead() {}

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

bool SentientActor::exits(const Actor* actor) const {
    if (actor->detectsExits())
        return overlaps(actor);
    return false;
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

void SentientActor::setDead() {
    if (!isDead())
        setm_dead();
}

bool SentientActor::blocks(double destX, double destY, const Actor *actor) const {
    // IMPORTANT: make the actor parameter this, because this is the thing you're checking destX and destY against
    return intersectsBoundingBox(destX, destY, this);
}

void SentientActor::setm_infected() {
    m_infected = true;
}

///////////////////////////////
/// Penelope Implementation ///
///////////////////////////////

/// Constructor/Destructor ///

Penelope::Penelope(double startX, double startY, StudentWorld* world)
        : SentientActor(IID_PLAYER, startX, startY, right, 0, world) {
    m_flames = 0;
    m_landmines = 0;
    m_vaccines = 0;
}

/// Accessors ///

int Penelope::getVaccines() const {
    return m_vaccines;
}

int Penelope::getLandmines() const {
    return m_landmines;
}

int Penelope::getFlames() const {
    return m_flames;
}

/// Mutators ///

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



/////////////////////////////
/// Zombie Implementation ///
/////////////////////////////

/// Constructor/Destructor ///

/// Accessors ///

bool Zombie::exits(const Actor *actor) const {
    return false;
}

/// Mutators ///

// some function here



/////////////////////////////////////////
/// EnvironmentalActor Implementation ///
/////////////////////////////////////////

/// Constructor/Destructor ///

EnvironmentalActor::EnvironmentalActor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world)
        : Actor(imageID, startX, startY, startDir, depth, world) {

}

/// Accessors ///

/// Mutators ///

// some function here



///////////////////////////
/// Wall Implementation ///
///////////////////////////

/// Constructor/Destructor ///

Wall::Wall(double startX, double startY, StudentWorld* world)
        : EnvironmentalActor(IID_WALL, startX, startY, right, 0, world) {}

/// Accessors ///

bool Wall::blocks(double destX, double destY, const Actor *actor) const {
    return (intersectsBoundingBox(destX, destY, this));
}

/// Mutators ///

void Wall::doSomething() {}



///////////////////////////
/// Exit Implementation ///
///////////////////////////

/// Constructor/Destructor ///

Exit::Exit(double startX, double startY, StudentWorld *world)
:EnvironmentalActor(IID_EXIT, startX, startY, right, 1, world) {

}

/// Accessors ///

// This checks if an actor in StudentWorld has overlapped with this object
bool Exit::citExits() const {
    list<Actor*> actors = getWorld()->actorList();
    list<Actor*>::iterator it;

    for (it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->exits(this))
            return true;
    }
    return false;
}

bool Exit::playerExits() const {
    return getWorld()->getPlayer()->exits(this);
}

// just denotes that it detects when something exits
bool Exit::detectsExits() const {
    return true;
}

/// Mutators ///

void Exit::doSomething() {
    // TODO: check for citizens exiting, implement once citizens are

    // debug statement to check for overlapping
    if (playerExits())
        cerr << "The player has touched the exit!" << endl;
    if (playerExits() && getWorld()->citsLeft() == 0) {
        getWorld()->setFinished();
    }
}



//////////////////////////
/// Pit Implementation ///
//////////////////////////

/// Constructor/Destructor ///

Pit::Pit(double startX, double startY, StudentWorld *world)
: EnvironmentalActor(IID_PIT, startX, startY, right, 0, world) {

}








































