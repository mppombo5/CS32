#include "Set.h"
using namespace std;

int main() {
    Set s;
    assert(s.empty());
    ItemType x = 9876543;
    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
    s.insert(123456789);
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == 123456789);


    cout << "All tests passed!" << endl;

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