//
// Created by Matthew Pombo on 2019-02-09.
//

#include <iostream>
#include <string>
using namespace std;

const char UPDATED = '#';

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = UPDATED;

    bool solved = false;

    // South
    if (maze[sr+1][sc] == '.') {
        solved = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    }
    // West
    if (!solved && maze[sr][sc-1] == '.') {
        solved = pathExists(maze, nRows, nCols, sr, sc - 1, er, ec);
    }
    //North
    if (!solved && maze[sr-1][sc] == '.') {
        solved = pathExists(maze, nRows, nCols, sr - 1, sc, er, ec);
    }
    // East
    if (!solved && maze[sr][sc+1] == '.') {
        solved = pathExists(maze, nRows, nCols, sr, sc +1, er, ec);
    }
    return solved;
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

    string maze1[10] = {
            "XXXXXXXXXX",
            "X...X....X",
            "XX.X..XX.X",
            "XX...X...X",
            "X.X.X..XXX",
            "X...X.X.XX",
            "X.X.X....X",
            "XXX.X.XX.X",
            "X...X..X.X",
            "XXXXXXXXXX",
    };

    string maze2[10] = {
            "XXXXXXXXXX",
            "X...X....X",
            "XX.X..XX.X",
            "XX...X...X",
            "X.X.X..XXX",
            "X...X.X.XX",
            "X.X.X....X",
            "XXX.X.XXXX",
            "X...X..X.X",
            "XXXXXXXXXX",
    };

    string maze3[10] = {
            "XXXXXXXXXX",
            "XXXXXXX..X",
            "XX.......X",
            "X..X....XX",
            "X..X..XXXX",
            "X..XXX.X.X",
            "XX...X...X",
            "X....XX..X",
            "XXX.....XX",
            "XXXXXXXXXX",
    };

    string maze4[10] = {
            "XXXXXXXXXX",
            "XXXXXXX..X",
            "XX.....X.X",
            "X..X....XX",
            "X..X..XXXX",
            "X..XXX.X.X",
            "XX...X...X",
            "X....XX..X",
            "XXX.....XX",
            "XXXXXXXXXX",
    };

    assert(pathExists(maze1, 10, 10, 1, 3, 8, 8));
    assert(!pathExists(maze2, 10, 10, 1, 3, 8, 8));
    assert(pathExists(maze3, 10, 10, 5, 6, 2, 8));
    assert(!pathExists(maze4, 10, 10, 5, 6, 2, 8));

    if (pathExists(maze, 10,10, 1,1, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return 0;
}