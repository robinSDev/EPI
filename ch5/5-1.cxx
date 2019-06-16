#include <bits/stdc++.h>
#define DNB(a) std::setw(3) << (a) << " : " << std::bitset<64>(a)
using namespace std;

bool precomputed_parity[1 << 16];

short brute_force_Parity(unsigned long long x) {
    short result = 0;
    while (x) {
        result += (x&1);
        x>>=1;
    }
    return result%2;
}

short Parity (unsigned long long x) {
    short result = 0;
    while (x)
    {
        result ^= 1;
        x &= (x-1);
    }
    return result;
}

short parity_XOR_firstHalf_with_secondHalf(unsigned long long x)
{
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >>  8;
    x ^= x >>  4;
    x ^= x >>  2;
    x ^= x >>  1;
    return x & 0x1;
}

void create_parity_cache(unsigned long long x, const std::string & fileFullName) {
    std::ofstream o(fileFullName);
    for (size_t i = 0; i < x; i++)
    {
        o << Parity(i) << "\n";
    }
}

void load_cache_to_array(std::string fileFullName)
{
    std::ifstream ipf(fileFullName);
    if(!ipf.is_open()) {
        std::cout << "Error opening file, map not created. Returning function call";
        return;
    }
        
    std::string sr;
    unsigned i = 0;
    while(ipf.good()) {
        std::getline(ipf, sr, '\n');
        if (sr != "")
        {
            precomputed_parity[i] = std::stoi(sr, nullptr, 2);
        }
        ++i;
    }
    ipf.close();
}

//Use 16 bit cache to reverse 64 unsigned
bool parity_64Bit_with_16bitCache(unsigned long long x)
{
    const int kWordSize = 16;
    const int kBitMask = 0xFFFF;
    return  precomputed_parity[ x >> (3 * kWordSize)            ] ^
            precomputed_parity[(x >> (2 * kWordSize)) & kBitMask] ^
            precomputed_parity[(x >>      kWordSize)  & kBitMask] ^
            precomputed_parity[ x                     & kBitMask];
}

int main () {
    std::string fileName = "parities.txt";
    create_parity_cache(1<<16, fileName);
    load_cache_to_array(fileName);
    unsigned long long x = 17513496196239327232;
    std::cout << parity_64Bit_with_16bitCache(x) << "\n";
    std::cout << parity_XOR_firstHalf_with_secondHalf(x);
    return 0;
}