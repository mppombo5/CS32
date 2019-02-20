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

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

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

    Level::LoadResult result = level.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level file " << levelFile << "." << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted." << endl;
    else if (result == Level::load_success) {
        cerr << "Successfully loaded level." << endl;

        m_citsLeft = 0;

        // level was loaded successfully, so we can start going through and adding each actor to m_actors.

        // nested for loops to check for each spot on the grid
        for (int i = 0; i < LEVEL_WIDTH; i++) {
            for (int k = 0; k < LEVEL_HEIGHT; k++) {
                const Level::MazeEntry& ge = level.getContentsOf(i, k);
                switch (ge) {
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
    }


    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    list<Actor*>::iterator it;
    // have each actor do something and check if the player died
    for (it = m_actors.begin(); it != m_actors.end(); it++) {
        (*it)->doSomething();
        if (m_player->isDead())
            return GWSTATUS_PLAYER_DIED;
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
    for (it = m_actors.begin(); it != m_actors.end(); it++) {
        if ((*it)->isDead()) {
            delete *it;
            m_actors.erase(it);

        }
    }

    // TODO: update game status line

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    return;
}

void StudentWorld::levelExample() {
    Level lev(assetPath());

    string levelFile = "level01.txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success) {
        cerr << "Successfully loaded level" << endl;

        Level::MazeEntry ge = lev.getContentsOf(5, 10); // level_x = 5, level_y = 10
        switch (ge) {                                   // so x=80 and y=160
            case Level::empty:
                cout << "Location 80, 160 is empty" << endl;
                break;
            case Level::smart_zombie:
                cout << "Location 80,160 starts with a smart zombie" << endl;
                break;
            case Level::dumb_zombie:
                cout << "Location 80,160 starts with a dumb zombie" << endl;
                break;
            case Level::player:
                cout << "Location 80,160 is where Penelope starts" << endl;
                break;
            case Level::exit:
                cout << "Location 80,160 is where an exit is" << endl;
                break;
            case Level::wall:
                cout << "Location 80,160 holds a Wall" << endl;
                break;
            case Level::pit:
                cout << "Location 80,160 has a pit in the ground" << endl;
                break;
            // etc...
        }
    }
}





















