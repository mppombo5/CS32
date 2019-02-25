#include "GameWorld.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::init()
{
    Level level(assetPath());
    // Now to figure out which level to load: "level" followed by two digits, the first of which might be 0
    string levelFile = "level";
    ostringstream oss;
    oss.fill('0');
    // Make sure to fill up 6 spaces: "xx.txt"
    string lvltxt = to_string(getLevel()) + ".txt";
    oss << setw(6) << lvltxt;
    levelFile += oss.str();
    // I just really hope they don't make more than 99 levels.

    Level::LoadResult levelResult = level.loadLevel(levelFile);

    // couldn't find level file, so we assume they won
    if (levelResult == Level::load_fail_file_not_found || getLevel() > 99) {
        cerr << "Cannot find level file " << levelFile << "." << endl;
        return GWSTATUS_PLAYER_WON;
    }
    // level file was improperly formatted
    else if (levelResult == Level::load_fail_bad_format) {
        cerr << "Your level was improperly formatted." << endl;
        return GWSTATUS_LEVEL_ERROR;
    }

    // level was loaded successfully, so we can go about our day
    else if (levelResult == Level::load_success) {
        cerr << "Successfully loaded level." << endl;

        m_citsLeft = 0;
        m_levelFinished = false;

        // first we loop through and add each actor to m_actors according to the level file
        // nested for loops to check for each spot on the grid
        for (int i = 0; i < LEVEL_WIDTH; i++) {
            for (int k = 0; k < LEVEL_HEIGHT; k++) {
                const Level::MazeEntry& objectAtCoords = level.getContentsOf(i, k);
                switch (objectAtCoords) {
                    // TODO: add each actor to m_actors according to its space (constructor coordinates)
                    case Level::empty:
                        cout << "Empty space at " << i << "," << k << endl;
                        break;
                    case Level::smart_zombie:
                        cout << "Smart zombie at " << i << "," << k << endl;
                        break;
                    case Level::dumb_zombie:
                        cout << "Dumb zombie at " << i << "," << k << endl;
                        break;
                    case Level::player:
                        cout << "Penelope starts at " << i << "," << k << endl;
                        m_player = new Penelope(i * SPRITE_WIDTH, k * SPRITE_HEIGHT, this);
                        break;
                    case Level::exit:
                        cout << "Exit at " << i << "," << k << endl;
                        m_actors.push_back(new Exit(i * SPRITE_WIDTH, k * SPRITE_HEIGHT, this));
                        break;
                    case Level::citizen:
                        m_citsLeft++;
                        cout << "Citizen at " << i << "," << k << endl;
                        break;
                    case Level::wall:
                        cout << "Wall at " << i << "," << k << endl;
                        m_actors.push_back(new Wall(i * SPRITE_WIDTH, k * SPRITE_HEIGHT, this));
                        break;
                    case Level::pit:
                        cout << "Pit at " << i << "," << k << endl;
                        break;
                    case Level::vaccine_goodie:
                        cout << "Vaccine at " << i << "," << k << endl;
                        break;
                    case Level::gas_can_goodie:
                        cout << "Gas can at " << i << "," << k << endl;
                        break;
                    case Level::landmine_goodie:
                        cout << "Landmine at " << i << "," << k << endl;
                        break;
                }
            }
        }
        return GWSTATUS_CONTINUE_GAME;
    }
    // I have no idea when this would be the case, but I figure this is as appropriate a response as any.
    else
        return GWSTATUS_LEVEL_ERROR;
}

// NOTE: to check which one to remove, just set it to dead
int StudentWorld::move()
{
    m_player->doSomething();
    list<Actor*>::iterator it;
    // have each actor do something and check if the player died
    for (it = m_actors.begin(); it != m_actors.end(); it++) {
        if (! (*it)->isDead())
            (*it)->doSomething();
        if (m_player->isDead())
            return GWSTATUS_PLAYER_DIED;
        if (m_levelFinished)
            return GWSTATUS_FINISHED_LEVEL;
        // TODO: check if the player has beaten the level (no cits left, Penelope has reached the exit)
    }

    // go through and delete/erase every actor that's dead
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if ((*it)->isDead()) {
            delete *it;
            // sets iterator to item after erased item
            it = m_actors.erase(it);
            continue;
        }
        // otherwise, just keep traversing
        it++;
    }

    // update the game status line
    ostringstream oss;
    oss << "Score: ";
    oss.fill('0');
    oss << setw(6) << getScore() << setw(0) << "  Level: ";
    oss.fill(' ');
    oss << setw(2) << getLevel() << setw(0) << "  Lives: " << getLives() << "  Vaccines: "
    << setw(2) << m_player->getVaccines() << setw(0) << "  Flames: " << setw(2) << m_player->getFlames()
    << setw(0) << "  Mines: " << setw(2) << m_player->getLandmines() << setw(0) << "  Infected: " << m_player->infectionCount();
    setGameStatText(oss.str());



    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        delete *it;
        it = m_actors.erase(it);
    }

    delete m_player;
}





























