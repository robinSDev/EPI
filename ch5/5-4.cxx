#include<iostream>
#include<bitset>
#include<iomanip>
#define DNB(a) std::setw(3) << (a) << " : " << std::bitset<64>(a) << "\n"

const int kNumUnsignBits = 64;

unsigned long long closestIntSameBitCount(unsigned long long x)
{
    for  (unsigned i = 0; i < kNumUnsignBits - 1; ++i)
    {
        if ( ((x >> i) & 1) != ( (x >> (i +1)) & 1) ) //check if bit 'i' and 'i+1' are unequal
        {
            x ^= (1ULL << i) | (1ULL << (i+1)); //swap bit 'i' with bit 'i+1'
            return x;
        }
    }
    //throw error if all bits are 0 or 1
    throw std::invalid_argument("All bits are 0 or 1");
    return 0;
}

int main()
{
    unsigned long long x = 19216811;
    std::cout << DNB(x);
    x = closestIntSameBitCount(x);
    std::cout << DNB(x);
    
    return 0;
}
