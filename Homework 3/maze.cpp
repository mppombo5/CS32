//
// Created by Matthew Pombo on 2019-02-09.
//

#include <string>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    char UPDATED = '#';

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