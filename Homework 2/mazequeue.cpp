//
// Created by Matthew Pombo on 2019-02-03.
//

#include <iostream>
#include <queue>
using namespace std;

const char UPDATED = ' ';

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> cQueue;
    cQueue.push(Coord(sr,sc));
    maze[sr][sc] = UPDATED;

    while (!cQueue.empty()) {
        Coord c = cQueue.front();
        cQueue.pop();
        if (c.r() == er && c.c() == ec)
            return true;
        // South
        if (maze[c.r()+1][c.c()] == '.') {
            cQueue.push(Coord(c.r()+1, c.c()));
            maze[c.r()+1][c.c()] = UPDATED;
        }
        // West
        if (maze[c.r()][c.c()-1] == '.') {
            cQueue.push(Coord(c.r(), c.c()-1));
            maze[c.r()][c.c()-1] = UPDATED;
        }
        // North
        if (maze[c.r()-1][c.c()] == '.') {
            cQueue.push(Coord(c.r()-1, c.c()));
            maze[c.r()-1][c.c()] = UPDATED;
        }
        // East
        if (maze[c.r()][c.c()+1] == '.') {
            cQueue.push(Coord(c.r(), c.c()+1));
            maze[c.r()][c.c()+1] = UPDATED;
        }
    }
    return false;
}

int main() {
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}