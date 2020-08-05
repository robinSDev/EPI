#include <bits/stdc++.h>
using namespace std;

int SearchEntryEqualToItsIndex(const vector<int> &A)
{
    int left = 0, right = A.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int difference = A[mid] - mid;
        //A[mid] == m if and only if difference = 0
        if (difference == 0)
        {
            return mid;
        }
        else if (difference > 0)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    vector<int> A = {-2, 0, 2, 3, 6, 7, 9};
    cout << SearchEntryEqualToItsIndex(A);
}