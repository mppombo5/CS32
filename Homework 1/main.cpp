#include "Set.h"
using namespace std;

int main() {
    Set s1;
    Set s2;

    s1.insert("one");
    s1.insert("two");
    s1.insert("three");
    s1.insert("seven");

    s2.insert("four");
    s2.insert("five");
    s2.insert("six");

    s1.swap(s2);

    s1.dump();
    cerr << "=====" << endl;
    s2.dump();

    /*cerr << "False is " << false << ',' << endl << "True is " << true << endl << "=====" << endl;

    s.insert("hi there");
    s.insert("general kenobi");
    s.insert("this is where the fun begins");

    s.dump();
    cerr << "=====" << endl;

    bool removed = false;
    removed = s.erase("general kenobi");

    s.dump();
    cerr << "Set size is " << s.size() << endl << "Erase returns " << removed << endl << "=====" << endl;
    removed = false;

    removed = s.erase("yep");

    s.dump();
    cerr << "Set size is " << s.size() << endl << "Erase returns " << removed;
     */

    return 0;
}