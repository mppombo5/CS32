//
// Created by Matthew Pombo on 2019-02-06.
//

bool somePredicate(double x);

// HELPFUL TIP: make a variable that represents the recursive function of the smaller subset
// then compare it

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
/// Implemented ///
int countTrue(const double a[], int n)
{
    if (n <= 0)
        return 0;

    int first = 0;
    int rest = 0;

    // if the somePredicate(a[0]) returns true, then add one to first
    if (somePredicate(a[0]))
        first++;
    // no matter what, the rest should still be totaled up using the "magic" function
    rest = countTrue(a+1, n-1);

    return first + rest;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
/// Implemented ///
// but look over it to understand why it works
int firstTrue(const double a[], int n)
{
    if (n <= 0)
        return -1;

    if (somePredicate(a[0]))
        return 0;
    int last = firstTrue(a+1, n-1);
    if (last == -1)
        return -1;
    else
        return 1+last;
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
/// Implemented ///
int positionOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1;

    if (n == 1)
        return 0;
    int first = positionOfMin(a, n-1);
    if (a[n-1] < a[first])
        return n-1;
    else
        return first;
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
    // THE ORDER MATTERS
    // it still has to return true if a1 runs out as a2 runs out
    if (n2 <= 0)
        return true;
    if (n1 <= 0) {
        return false;
    }

    if (a1[0] == a2[0]) {
        // this works because if n2 has run out, then that's good
        // if n1 has run out, on the other hand, then it didn't match and that's no bueno
        return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }

    return includes(a1 + 1, n1 - 1, a2, n2);
}