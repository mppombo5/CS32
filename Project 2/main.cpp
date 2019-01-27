#include <iostream>
#include <cassert>
#include <cmath>
#include "Set.h"
using namespace std;

int main() {

    // In case anyone sees this test routine, "David" is my friend David Yu – NOT professor Smallberg.

    /*
    Set s;

    s.insert("david");
    s.insert("sucks");
    s.insert("ass");
    s.insert("and chokes on it lmao");

    s.erase("and chokes on it lmao");

    string contained = "and chokes on it lmao";

    assert(!s.contains(contained));

    s.dump();

    cout << endl;

    s.dumpBackwards();

    cout << endl << "This list is " << s.size() << " elements long." << endl << endl;

    Set ss;

    ss.insert("temp");
    ss.insert("lmao");

    ss = s;

    ss.dump();

    cout << endl;

    ss.dumpBackwards();

    cout << endl << "List ss is " << ss.size() << " elements long." << endl << endl;
     */

    Set ss;
    ss.insert("lavash");
    ss.insert("roti");
    ss.insert("chapati");
    ss.insert("injera");
    ss.insert("roti");
    ss.insert("matzo");
    ss.insert("injera");
    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
    string x;
    ss.get(0, x);
    assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
    ss.get(4, x);
    assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
    ss.get(2, x);
    assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss

    Set ss1;
    ss1.insert("laobing");
    ss1.insert("bread");
    //ss1.erase("bread");
    Set ss2;
    ss2.insert("matzo");
    ss2.insert("pita");
    //ss2.erase("pita");
    ss1.swap(ss1);
    assert(ss1.size() == 2 && ss1.contains("laobing") && ss1.contains("bread"));
    ss1.swap(ss2);
    assert(ss1.size() == 2  &&  ss1.contains("matzo")  && ss1.contains("pita") &&
           ss2.size() == 2  &&  ss2.contains("laobing") && ss2.contains("bread"));

    Set ss3;
    ss3.insert("dosa");
    assert(!ss3.contains(""));
    ss3.insert("tortilla");
    ss3.insert("");
    ss3.insert("focaccia");
    assert(ss3.contains(""));
    ss3.erase("dosa");
    assert(ss3.size() == 3  &&  ss3.contains("focaccia")  &&  ss3.contains("tortilla")  &&
           ss3.contains(""));
    string v;
    assert(ss3.get(1, v)  &&  v == "focaccia");
    assert(ss3.get(0, v)  &&  v == "");

    Set s;
    assert(s.empty());
    ItemType y = "arepa";
    assert( !s.get(42, y)  &&  y == "arepa"); // x unchanged by get failure
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, y)  &&  y == "chapati");

    Set ss4;  // ItemType is std::string
    ss4.insert("ccc");
    ss4.insert("aaa");
    ss4.insert("bbb");
    ItemType x1 = "xxx";
    assert(!ss4.get(3, x1)  &&  x1 == "xxx");  // x is unchanged
    assert(ss4.get(1, x1)  &&  x1 == "bbb");

    Set u1;
    u1.insert("hello");
    u1.insert("there");
    u1.insert("general");
    u1.insert("kenobi");


    Set u2;
    u2.insert("you");
    u2.insert("are");
    u2.insert("general");
    u2.insert("kenobi");
    unite(u1, u2, ss);
    assert(ss.size() == 6);
    assert(ss.contains("are") && ss.contains("hello") && ss.contains("general") && ss.contains("kenobi"));
    ss.dump();

    cerr << "====" << endl;

    unite(u1, u1, ss);
    assert(ss.size() == u1.size());
    ss.dump();

    cerr << "====" << endl;

    subtract(u1, u1, ss);
    assert(ss.empty());
    ss.dump();

    cerr << "====" << endl;
    unite(u1, u2, u1);
    assert(u1.size() == 6);
    assert(u1.contains("you") && u1.contains("are"));
    u1.dump();

    cerr << "====" << endl;
    subtract(u1, u2, u1);
    u1.dump();
    assert(u1.size() == 2);
    assert(u1.contains("hello") && u1.contains("there"));
    assert(!u1.contains("you") && !u1.contains("are"));


    Set q;
    q.insert("bro");
    q.insert("I");
    q.insert("went");
    q.insert("to");
    q.insert("bed");
    q.insert("5am");
    q.erase("bro");
    q.erase("5am");
    assert(q.size() == 4);
    assert(!q.contains("bro") && !q.contains("5am"));

    cout << "Passed all tests" << endl;

    /////////////////
    /// Int tests ///
    /////////////////
    // 2 8 3 9 5
    // 6 3 8 5 10
    // 9 3 6 5 10 2 8

    /* int tests
    int s1list[5] = {
            2,  8, 3, 9, 5
    };
    int s2list[5] = {
            6, 3, 8, 5, 10
    };
    int unitelist[7] = {
            9, 3, 6, 5, 10, 2, 8
    };
    int sublist[2] = {
            9, 2
    };

    Set s1;
    Set s2;
    Set u;

    s1.insert(2);
    s1.insert(8);
    s1.insert(3);
    s1.insert(9);
    s1.insert(5);

    s2.insert(6);
    s2.insert(3);
    s2.insert(8);
    s2.insert(5);
    s2.insert(10);

    u.insert(69);

    unite(s1, s2, u);
    for (int i = 0; i < 7; i++) {
        assert(u.contains(unitelist[i]));
    }
    assert(u.size() == 7);

    subtract(s1, s2, u);
    assert(u.size() == 2);
    for (int i = 0; i < 2; i++) {
        assert(u.contains(sublist[i]));
    }
    u.dump();


    u.insert(69);

    cout << "Passed all tests!" << endl;
     */

    return 0;
}

#include "Set.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Set>::value,
              "Set must be default-constructible.");
static_assert(std::is_copy_constructible<Set>::value,
              "Set must be copy-constructible.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Set::operator=, Set& (Set::*)(const Set&));
    CHECKTYPE(&Set::empty,     bool (Set::*)() const);
    CHECKTYPE(&Set::size,      int  (Set::*)() const);
    CHECKTYPE(&Set::insert,    bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::erase,     bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::contains,  bool (Set::*)(const ItemType&) const);
    CHECKTYPE(&Set::get,       bool (Set::*)(int, ItemType&) const);
    CHECKTYPE(&Set::swap,      void (Set::*)(Set&));
    CHECKTYPE(unite,           void (*)(const Set&, const Set&, Set&));
    CHECKTYPE(subtract,        void (*)(const Set&, const Set&, Set&));
}