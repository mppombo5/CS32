//
// Created by Matthew Pombo on 2019-02-09.
//

#include <iostream>
#include <string>
#include <stack>
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
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = UPDATED;

    bool solnFound = false;

    // South
    if (maze[sr+1][sc] == '.') {
        return pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    }
    // West
    if (maze[sr][sc-1] == '.') {
        return pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    }
    //North
    if (maze[sr-1][sc] == '.') {
        solnFound = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    }
    // East
    if (maze[sr][sc-1] == '.') {
        solnFound = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    }

    return solnFound;
}

int main() {
    string maze[10] = {
            "XXXXXXXXXX",
            "X....X...X", //                         |
            "X.XX.XX..X", //                         V
            "XXX....X.X", // starting point above XXX.XXXX
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
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << maze[i] << endl;
    }
    return 0;
}