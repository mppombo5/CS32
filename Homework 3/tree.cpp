//
// Created by Matthew Pombo on 2019-02-11.
//

#include <iostream>
#include <cassert>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    return -999;  // This is incorrect.
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > divider
//   * for firstNotGreater <= i < firstLess, a[i] == divider
//   * for firstLess <= i < n, a[i] < divider
// All the elements > divider end up in no particular order.
// All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
            int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;

    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > divider
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == divider
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < divider

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    if (n <= 1)
        return;

    int fNG, fL;

    double divider = a[0];
    divide(a, n, divider, fNG, fL);

    order(a, fNG);
    order(&a[fL], n-fL);
}

template <typename item>
void printList(item a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
}

int main() {
    double nums[10] {
        6, 92, 6, 63, 5, 10, 6, 8, 52, 24
    };
    order(nums, 10);
    //printList(nums, 10);
    for (int i = 1; i < 10; i++) {
        assert(nums[i] <= nums[i-1]);
    }

    double nums1[10] {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
    order (nums1, 10);
    //printList(nums1, 10);
    for (int i = 1; i < 10; i++) {
        assert(nums1[i] <= nums1[i-1]);
    }
    //cout << "====" << endl;
    double nums2[10] {
        1, 2, 3, 45, 56, 67, 7, 8, 11, 423
    };
    order(nums2, 10);
    // fixed it ayy
    printList(nums2, 10);
    for (int i = 1; i < 10; i++) {
        assert(nums2[i] <= nums2[i-1]);
    }

    double nums3[11] {
        1, 3, 2, 56, 45, 8, 7, 67, 11, 432, 572
    };
    order(nums3, 11);
    for (int i = 1; i < 11; i++) {
        assert(nums3[i] <= nums3[i-1]);
    }

    double nums4[11] {
            1, 2, 3, 45, 56, 67, 7, 8, 11, 423, 424
    };
    order(nums4, 11);
    for (int i = 1; i < 11; i++) {
        assert(nums4[i] <= nums4[i-1]);
    }

    double nums5[31] {
            534.15, 160.02, 295.04, 269.4, 170.37, 326.77, 418.76, 390.29,
            225.47,79.5,594.6,137.1,64.23,399.53,567.59,187.12,510.51,
            182.73,365.12,226.45,43.03,22.78,200.8,433.68,379.44,
            117.57,457.7,153.07,458.17,545.76,0
    };
    order(nums5, 31);
    //for (int k = 0; k < 29; k++) {
    //    nums5[30] = nums5[k];
        for (int i = 1; i < 31; i++) {
            assert(nums5[i] <= nums5[i-1]);
        }
    //}
    //printList(nums5, 30);

    double nums6[60] {
            425.62,225.51,8.64,50.5,385.24,369.38,402.61,564.24,408.24,
            538.71,468.51,504.54,458.3,229.1,575.07,591.04,192.29,590.31,
            359.57,401.28,149.39,480.25,494.64,172.39,203.81,177.15,
            82.12,241.92,457.95,102.93,8.85,295.45,24.21,190.15,93.74,
            21.43,147.51,18.61,33.09,460.53,489.96,84.86,356.75,119.75,
            356.67,396.29,390.7,391.07,320.2,89.21,470.08,52.45,247.93,
            279.59,587.34,161.32,118.07,430.97,213.15,188.25
    };
    order(nums6, 60);
    printList(nums6, 60);
    for (int i = 1; i < 60; i++) {
        assert(nums6[i] <= nums6[i-1]);
    }

    cout << "====" << endl;
    // just a test
    double d = 3.67;
    d++;
    cout << d << endl;

    cout << "All tests passed!" << endl;
}