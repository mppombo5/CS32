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
    // otherX <=        destX         <= otherX+SPRITE_WIDTH-1
    // otherX <= destX+SPRITE_WIDTH-1 <= otherX+SPRITE_WIDTH-1
    // and
    // otherY <=         destY         <= otherY+SPRITE_HEIGHT-1
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
    m_infected = false;
    m_infectionCount = 0;
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

bool Actor::blocksFlames(double destX, double destY, const Actor *actor) const {
    return false;
}

bool Actor::isDead() const {
    return m_dead;
}

// Important distinction:
// "blocked" checks whether or not the actor *is movementBlocked* by any of StudentWorld's actors
// "blocks" means it blocksMovement the movement of an actor to a destination
bool Actor::movementBlocked(double destX, double destY) const {
    return getWorld()->hasActorBlockingMovement(destX, destY, this);
}

bool Actor::flameBlocked(double destX, double destY) const {
    return getWorld()->hasActorBlockingFlames(destX, destY, this);
}

bool Actor::overlaps(const Actor* other) const {
    // "XC" and "YC" mean "XCenter" and "YCenter"
    // static cast to double in order to avoid integer division (maybe redundant, maybe not)
    double srcXC = getX() + (static_cast<double>(SPRITE_WIDTH)/2);
    double srcYC = getY() + (static_cast<double>(SPRITE_HEIGHT)/2);
    double otherXC = other->getX() + (static_cast<double>(SPRITE_WIDTH)/2);
    double otherYC = other->getY() + (static_cast<double>(SPRITE_HEIGHT)/2);

    // "dX" means delta(X)
    double dX = otherXC - srcXC;
    double dY = otherYC - srcYC;

    return (dX * dX) + (dY * dY) <= 100;
}

bool Actor::isInfected() const {
    return m_infected;
}

int Actor::infectionCount() const {
    return m_infectionCount;
}

StudentWorld* Actor::getWorld() const {
    return m_world;
}

/// Mutators ///

// simply makes it easier to make something move, as the check is built-in
void Actor::safeMoveTo(double destX, double destY) {
    if (!movementBlocked(destX, destY))
        moveTo(destX, destY);
}

void Actor::increaseInfection() {
    m_infectionCount++;
}

void Actor::setm_dead() {
    m_dead = true;
}

void Actor::infect() {}

void Actor::setm_infected() {
    m_infected = true;
}

////////////////////////////////////
/// SentientActor Implementation ///
////////////////////////////////////

/// Constructor/Destructor ///

SentientActor::SentientActor(int imageID, double startX, double startY, Direction startDir, int depth, StudentWorld* world)
        : Actor(imageID, startX, startY, startDir, depth, world) {
}

/// Accessors ///

bool SentientActor::exits(const Actor* actor) const {
    if (actor->detectsExits())
        return overlaps(actor);
    return false;
}

bool SentientActor::fallsIntoPits() const {
    return true;
}

bool SentientActor::damagedByFlame() const {
    return true;
}

bool SentientActor::triggersLandmines() const {
    return true;
}

/// Mutators ///

// TODO: when zombies are implemented, they shouldn't be infected
void SentientActor::infect() {
    if (!isInfected())
        setm_infected();
}

void SentientActor::setDead() {
    if (!isDead())
        setm_dead();
}

bool SentientActor::blocksMovement(double destX, double destY, const Actor *actor) const {
    // IMPORTANT: make the actor parameter this, because this is the thing you're checking destX and destY against
    return intersectsBoundingBox(destX, destY, this);
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

void Penelope::addVaccine() {
    m_vaccines++;
}

void Penelope::addFlames() {
    m_flames += 5;
}

void Penelope::addLandmines() {
    m_landmines += 2;
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

bool EnvironmentalActor::fallsIntoPits() const {
    return false;
}

// Environmental actors (except landmines) are not damaged by flames, but goodies are
bool EnvironmentalActor::damagedByFlame() const {
    return false;
}

bool EnvironmentalActor::triggersLandmines() const {
    return false;
}

bool EnvironmentalActor::blocksMovement(double destX, double destY, const Actor *actor) const {
    return false;
}

/// Mutators ///

void EnvironmentalActor::setDead() {
    if (!isDead())
        setm_dead();
}



///////////////////////////
/// Wall Implementation ///
///////////////////////////

/// Constructor/Destructor ///

Wall::Wall(double startX, double startY, StudentWorld* world)
        : EnvironmentalActor(IID_WALL, startX, startY, right, 0, world) {}

/// Accessors ///

bool Wall::blocksFlames(double destX, double destY, const Actor* actor) const {
    return true;
}

bool Wall::blocksMovement(double destX, double destY, const Actor *actor) const {
    return (intersectsBoundingBox(destX, destY, this));
}

/// Mutators ///

void Wall::doSomething() {}

// walls should never be set to dead
void Wall::setDead() {}



///////////////////////////
/// Exit Implementation ///
///////////////////////////

/// Constructor/Destructor ///

Exit::Exit(double startX, double startY, StudentWorld *world)
:EnvironmentalActor(IID_EXIT, startX, startY, right, 1, world) {

}

/// Accessors ///

// This checks if an actor in StudentWorld has overlapped with this object
// TODO: move the loop to the StudentWorld class
/*bool Exit::citExits() const {
    list<Actor*> actors = getWorld()->getActors();
    list<Actor*>::iterator it;

    for (it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->exits(this))
            return true;
    }
    return false;
}*/

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
    //if (playerExits())
    //    cerr << "The player has touched the exit!" << endl;
    if (playerExits() && getWorld()->citsLeft() == 0) {
        getWorld()->setFinished();
    }
}

// exits should never be dead
void Exit::setDead() {}

bool Exit::blocksFlames(double destX, double destY, const Actor* actor) const {
    return true;
}



//////////////////////////
/// Pit Implementation ///
//////////////////////////

/// Constructor/Destructor ///

Pit::Pit(double startX, double startY, StudentWorld *world)
: EnvironmentalActor(IID_PIT, startX, startY, right, 0, world) {

}

/// Mutators ///

void Pit::doSomething() {
    Penelope* player = getWorld()->getPlayer();
    if (player->overlaps(this)) {
        player->setDead();
    }

    getWorld()->killOverlappingActors(this, fallsIntoPits());

    // just here in case killOverlappingActors doesn't work
    /*list<Actor*> actors = getWorld()->getActors();
    list<Actor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        Actor* actor = *it;
        if (actor->overlaps(this) && actor->fallsIntoPits())
            actor->setDead();
    }*/
}

// pits should never be dead
void Pit::setDead() {}



////////////////////////////
/// Flame Implementation ///
////////////////////////////

/// Constructor/Destructor ///

Flame::Flame(double startX, double startY, Direction dir, StudentWorld *world)
: EnvironmentalActor(IID_FLAME, startX, startY, dir, 0, world) {
    m_ticksAlive = 0;
}

/// Mutators ///

void Flame::doSomething() {
    m_ticksAlive++;

    if (isDead())
        return;

    if (m_ticksAlive > 2) {
        setDead();
        return;
    }

    getWorld()->killOverlappingActors(this, damagedByFlame());
}



////////////////////////////
/// Vomit Implementation ///
////////////////////////////

/// Constructor ///

Vomit::Vomit(double startX, double startY, Direction dir, StudentWorld *world)
: EnvironmentalActor(IID_VOMIT, startX, startY, dir, 0, world) {

}

/// Mutators ///

void Vomit::doSomething() {
    m_ticksAlive++;

    if (isDead())
        return;

    if (m_ticksAlive > 2) {
        setDead();
        return;
    }

    getWorld()->infectOverlappingActors(this);
}



///////////////////////////////
/// Landmine Implementation ///
///////////////////////////////

/// Constructor ///

Landmine::Landmine(double startX, double startY, StudentWorld *world)
: EnvironmentalActor(IID_LANDMINE, startX, startY, right, 1, world) {
    m_safetyTicks = 30;
}

/// Accessors ///

bool Landmine::damagedByFlame() const {
    return true;
}

bool Landmine::isActive() const {
    return m_safetyTicks <= 0;
}

/// Mutators ///

void Landmine::doSomething() {
    if (isDead())
        return;

    if (!isActive()) {
        m_safetyTicks--;
        return;
    }

    if (getWorld()->hasOverlappingActor(this, triggersLandmines())) {
        setDead();
        getWorld()->playSound(SOUND_LANDMINE_EXPLODE);

        // nested for loops to add flames in a 3x3 pattern
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // go from -1 to 1, so that would be -1 + i or j
                int multX = -1 + i;
                int multY = -1 + j;
                double destX = getX() + (SPRITE_WIDTH * multX);
                double destY = getY() + (SPRITE_HEIGHT * multY);
                if (!flameBlocked(destX, destY))
                    getWorld()->addActor(new Flame(destX, destY, right, getWorld()));
            }
        }
        getWorld()->addActor(new Pit(getX(), getY(), getWorld()));
    }
}



/////////////////////////////
/// Goodie Implementation ///
/////////////////////////////

/// Constructor ///

Goodie::Goodie(int imageID, double startX, double startY, StudentWorld *world)
: EnvironmentalActor(imageID, startX, startY, right, 1, world) {

}

/// Accessors ///

bool Goodie::damagedByFlame() const {
    return true;
}

/// Mutators ///

// the goodies' implementations of doSomething would be nearly identical – so they're all in one with
// a single differentiated function.
void Goodie::doSomething() {
    if (isDead())
        return;

    Penelope* player = getWorld()->getPlayer();
    if(!player->isDead() && player->overlaps(this)) {
        getWorld()->increaseScore(50);
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        // THIS is what differentiates the goodies from each other – what they add to the player's inventory
        addToInventory();
    }
}



//////////////////////////////
/// Vaccine Implementation ///
//////////////////////////////

/// Constructor ///

Vaccine::Vaccine(double startX, double startY, StudentWorld *world)
: Goodie(IID_VACCINE_GOODIE, startX, startY, world) {

}

/// Mutators ///

void Vaccine::addToInventory() {
    getWorld()->getPlayer()->addVaccine();
}



/////////////////////////////
/// GasCan Implementation ///
/////////////////////////////

/// Constructor ///

GasCan::GasCan(double startX, double startY, StudentWorld *world)
: Goodie(IID_GAS_CAN_GOODIE, startX, startY, world) {

}

/// Mutators ///

void GasCan::addToInventory() {
    getWorld()->getPlayer()->addFlames();
}



/////////////////////////////////////
/// LandmineGoodie Implementation ///
/////////////////////////////////////

/// Constructor ///

LandmineGoodie::LandmineGoodie(double startX, double startY, StudentWorld *world)
: Goodie(IID_LANDMINE_GOODIE, startX, startY, world) {

}

/// Mutators ///

void LandmineGoodie::addToInventory() {
    getWorld()->getPlayer()->addLandmines();
}




































