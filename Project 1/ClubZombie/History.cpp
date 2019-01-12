//
// Created by Matthew Pombo on 2019-01-11.
//

#include <iostream>

#include "History.h"
using namespace std;

History::History(int nRows, int nCols) {
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < nRows; i++) {
        for (int k = 0; k < nCols; k++) {
            m_grid[i][k] = 0;
        }
    }
}

bool History::record(int r, int c) {
    if (r < 1 || r > m_rows || c < 1 || c > m_cols)
        return false;
    else {
        m_grid[r-1][c-1]++;
        return true;
    }
}

void History::display() const {
    clearScreen();
    for (int i = 0; i < m_rows; i++) {
        for (int k = 0; k < m_cols; k++) {
            cout << gridToChar(m_grid[i][k]);
        }
        cout << endl;
    }
    cout << endl;
}