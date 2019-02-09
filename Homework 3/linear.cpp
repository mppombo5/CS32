//
// Created by Matthew Pombo on 2019-02-06.
//

//////////////////////////////////////////////////
/// REMEMBER TO DELETE THESE BEFORE TURNING IN ///
//////////////////////////////////////////////////
#include <iostream>
#include <cassert>
using namespace std;

bool somePredicate(double x);

bool somePredicate(double x) {
    return x > 30;
}


// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.
/// Implemented ///
bool anyTrue(const double a[], int n)
{
    if (n <= 0)
        return false;

    // if somePredicate of the first element returns true, then return true
    if (somePredicate(a[0]))
        return true;
    // if not, examine the rest
    else
        return anyTrue(a+1, n-1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n <= 0)
        return 0;

    int first = 0;
    int rest = 0;

    // if the somePredicate(a[0]) returns true, then add one to first
    if (somePredicate(*a))
        first++;
    // no matter what, the rest should still be totaled up using the "magic" function
    rest = countTrue(a+1, n-1);

    return first + rest;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    return -999;  // This is incorrect.
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMin(const double a[], int n)
{
    return -999;  // This is incorrect.
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    return false;  // This is not always correct.
}

/////////////////////////////////////////////////
/// REMEMBER TO DELETE THIS BEFORE TURNING IN ///
/////////////////////////////////////////////////
int main() {
    const double arrAnyTrue[10] {
        1, 2, 3, 4, 5, 35, 7, 8, 9, 10
    };

    const double arrCountTrue[10] {
        1, 2, 3, 45, 55, 65, 7, 8, 95, 10
    };

    // anyTrue tests
    assert(anyTrue(arrAnyTrue, 10));
    assert(anyTrue(arrAnyTrue+5, 5));
    assert(! anyTrue(arrAnyTrue+6, 4));
    assert(! anyTrue(arrAnyTrue, 5));
    assert(!anyTrue(arrAnyTrue, 0));

    // countTrue tests
    assert(countTrue(arrCountTrue, 10) == 4);
    assert(countTrue(arrCountTrue+4, 6) == 3);
    assert(countTrue(arrAnyTrue, 10) == 1);
    assert(countTrue(arrCountTrue+5, 5) == 2);
    assert(countTrue(arrAnyTrue+6, 4) == 0);

    cout << "All tests passed!" << endl;

    return 0;
}