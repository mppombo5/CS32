#include <iostream>
#include <cassert>
#include "Set.h"
using namespace std;

int main() {

    // In case anyone sees this test routine, "David" is my friend David Yu – NOT professor Smallberg.

    /*Set s;

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

    cout << endl << "List ss is " << ss.size() << " elements long." << endl << endl;*/

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

    cout << "Passed all tests" << endl;

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
    //CHECKTYPE(unite,    void (*)(const Set&, const Set&, Set&));
    //CHECKTYPE(subtract, void (*)(const Set&, const Set&, Set&));
}