#include <bits/stdc++.h>
#define USL unsigned long
#define US unsigned
#define BS16 (std::bitset<16>)
#define DNB(a) std::setw(3) << (a) << " : " << std::bitset<8>(a)
using namespace std;

short bfParity(USL x) {
    short result = 0;
    while (x) {
        result += (x&1);
        x>>=1;
    }
    return result%2;
}

short Parity (USL x) {
    short result = 0;
    while (x)
    {
        result ^= 1;
        x &= (x-1);
    }
    return result;
}

void computeParity(USL x) {
    std::ofstream o("parities.txt");
    for (size_t i = 0; i < x; i++)
    {
        o << i << "," <<BS16(i) << "," << Parity(i) << std::endl;
    }
}

int main () {
    //computeParity(pow(2,16));
    return 0;
}