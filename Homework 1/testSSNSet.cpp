//
// Created by Matthew Pombo on 2019-01-22.
//
#include <iostream>
#include <cassert>
#include "SSNSet.h"

int main() {

    SSNSet s;
    s.add(1234);
    s.add(3456);
    s.add(6969);
    s.add(420420);
    s.add(1234);

    cout << "The SSNSet is " << s.size() << " numbers long." << endl;

    s.print();

    SSNSet s1;
    s1 = s;
    s1.add(5318008);
    s1.print();
    s.print();

    return 0;
}