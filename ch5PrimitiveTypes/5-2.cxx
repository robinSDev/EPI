#include<iostream>
#include<bitset>
#include<iomanip> //setw
#define DNB(a) std::setw(10) << (a) << " : " << std::bitset<64>(a)

long swapBits(long x, unsigned i, unsigned j)
{
    if ( (x>>i & 1) != (x>>j & 1))
    {
        long mask = (1L<<i) | (1L<<j);
        std::cout << DNB(mask) << "\n\n";
        x ^= mask;
    }
    return x;
}

int main()
{
    long x = 7799995;
    long res = swapBits(x, 10, 15);
    std::cout << DNB(res);
    return 0;
}