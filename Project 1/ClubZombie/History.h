//
// Created by Matthew Pombo on 2019-01-11.
//

#ifndef CLUBZOMBIE_HISTORY_H
#define CLUBZOMBIE_HISTORY_H

#include "globals.h"

class Arena;

class History {
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_grid[MAXROWS][MAXCOLS];
};


#endif //CLUBZOMBIE_HISTORY_H
