#include <bits/stdc++.h>
#define USL unsigned long
#define US unsigned
#define BS16 (std::bitset<16>)
#define DNB(a) std::setw(10) << (a) << " : " << std::bitset<32>(a)
using namespace std;

long swapBits(long x, unsigned i, unsigned j)
{
    if ( (x>>i & 1) != (x>>j & 1))
    {
        long mask = (1L<<i) | (1L<<j);
        cout << DNB(mask) << "\n\n";
        x ^= mask;
    }
    return x;
}

int main()
{
    long x = 7799995;
    long res = swapBits(x, 10, 15);
    cout << DNB(res);
    return 0;
}