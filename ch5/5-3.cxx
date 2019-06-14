#include <bits/stdc++.h>
#define USL unsigned long
#define US unsigned
#define BS16 (std::bitset<16>)
#define DNB(a) std::setw(10) << (a) << " : " << std::bitset<64>(a)
using namespace std;

unsigned long long reverseBitsUnsigned (unsigned long long x);
unsigned reverse16BitUnsignedImproved (unsigned x);
long long reverseBits (long long x);
long long reverseBitsImproved (long long x);
void calc_16Bit_reverse(const unsigned x);
void cacheFileToMap(string fileName);
void printMap();
std::unordered_map<std::bitset<16>, std::bitset<16>> m;

int main ()
{
    /*unsigned long long x = 929999;
    cout << DNB(x) << endl;
    x = reverseBits(x);
    cout << DNB(x) << endl;
    x = reverseBitsImproved(929999);
    cout << DNB(x) << endl;
    */
    //calc_16Bit_reverse(pow(2,16));
    //cacheFileToMap("16bitReverseBitSet.txt");
    bitset<16>("0000000000000111");
    //printMap();
    return 0;
}
/*TODO & PUSH TO GIT */
void cacheFileToMap(string fileName)
{
    std::ifstream ipf(fileName);
    if(!ipf.is_open())
        std::cout << "Error opening file";
    string sn, sr;
    while(ipf.good()) {
        getline(ipf, sn, ',');
        getline(ipf, sr, '\n');
        bitset<16> bn = bitset<16>(sn);
        bitset<16> br = bitset<16>(sr);
        m[bn] = br;
    }
    ipf.close();
}

void printMap()
{
    for(auto &elem : m)
    {
        std::cout << elem.first << " " << elem.second << "\n";
    }
}

//create a file and save all 16 bit numbers and its reverse
void calc_16Bit_reverse(const unsigned x)
{
    ofstream o("16bitReverse.txt");
    for (unsigned i = 0; i < x; i++) {
        o << i << "," << reverse16BitUnsignedImproved(i) << "\n";
    }
}

unsigned reverse16BitUnsignedImproved (unsigned x)
{
    unsigned mask = 0;
    for(unsigned i = 0, j = 15; i < j; ++i, --j)
    {
        if ( (x>>i & 1) != (x>>j & 1))
        {
            mask |= (1<<i) | (1<<j);
        }
    }
    x ^= mask;
    return x;
}
// UNSIGNED VERSION
unsigned long long reverseBitsUnsigned (unsigned long long x)
{
    for(unsigned i = 0, j = 63; i < j; ++i, --j)
    {
        cout << i << " " << j << endl;
        if ( (x>>i & 1) != (x>>j & 1))
        {
            unsigned long long mask = (1LL<<i) | (1LL<<j);
            cout << "   " << DNB(mask) << endl ;
            x ^= mask;
            //cout << "x changed\n" << DNB(x) << "\n";
        }
    }
    cout << DNB(x);
    return x;
}

//SIGNED VERSION
long long reverseBits (long long x)
{
    for(unsigned i = 0, j = 62; i < j; ++i, --j)
    {
        //cout << i << " " << j << endl;
        if ( (x>>i & 1) != (x>>j & 1))
        {
            long long mask = (1LL<<i) | (1LL<<j);
            //cout << "   " << DNB(mask) << endl ;
            x ^= mask;
            //cout << "x changed\n" << DNB(x) << "\n";
        }
    }
    return x;
}

//IMPROVED VERSION : CREATING ONE MASK THEN XOR WITH X
long long reverseBitsImproved (long long x)
{
    long long mask = 0LL;
    for(unsigned i = 0, j = 62; i < j; ++i, --j)
    {
        //cout << i << " " << j << endl;
        if ( (x>>i & 1) != (x>>j & 1))
        {
            mask |= (1LL<<i) | (1LL<<j);
            //cout << "   " << DNB(mask) << endl ;
            //cout << "x changed\n" << DNB(x) << "\n";
        }
    }
    x ^= mask;
    return x;
}
