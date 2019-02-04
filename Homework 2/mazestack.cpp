//
// Created by Matthew Pombo on 2019-02-02.
//

#include <iostream>
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
    stack<Coord>  cStack;

    cStack.push(Coord(sr,sc));
    maze[sr][sc] = UPDATED;

    while (!cStack.empty()) {
        Coord c = cStack.top();
        cStack.pop();
        if (c.r() == er && c.c() == ec)
            return true;
        if (maze[c.r()+1][c.c()] == '.') {
            cStack.push(Coord(c.r()+1, c.c()));
            maze[c.r()+1][c.c()] = UPDATED;
        }
        if (maze[c.r()][c.c()-1] == '.') {
            cStack.push(Coord(c.r(), c.c()-1));
            maze[c.r()][c.c()-1] = UPDATED;
        }
        if (maze[c.r()-1][c.c()] == '.') {
            cStack.push(Coord(c.r()-1, c.c()));
            maze[c.r()-1][c.c()] = UPDATED;
        }
        if (maze[c.r()][c.c()+1] == '.') {
            cStack.push(Coord(c.r(), c.c()+1));
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