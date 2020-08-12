#include<iostream>
#include<bitset>
#include<fstream> //ofstream and ifstream
#include<iomanip>//setw
#include<unordered_map>
#include<array>

#define DNB(a) std::setw(10) << (a) << " : " << std::bitset<64>(a)

//Reverse k bits
unsigned long long reverse_kBits_Unsigned (unsigned long long x, const unsigned k);
long long reverse_kBits_Signed (long long x, const unsigned k);
//Creating 16 bit Cache:
void calc_16Bit_reverse_cache_file(const unsigned x, const std::string &fileName);
void load_cache_to_array(std::string fileName);
void print_array();
//Use 16 bit cache to reverse 64 unsigned
unsigned long long reverse64Bit_with_16bitCache(unsigned long long x);

//Loading the cache from secondary memory to primary memory as an array
std::array<unsigned long long, 1 << 16> precomputed_reverse;

int main ()
{
    //std::cout << std::bitset<32>(1<<16);
    std::string fileName = "16bitReverse.txt";
    //calc_16Bit_reverse_cache_file(1<<16, fileName);
    load_cache_to_array(fileName);
    //print_array();
    unsigned long long x, y = 929999;
    x = reverse_kBits_Unsigned(y, 64);
    std::cout << DNB(x) << std::endl;
    
    x = reverse64Bit_with_16bitCache(y);
    std::cout << DNB(x) << std::endl;
    
    return 0;
}

//Use 16 bit cache to reverse 64 unsigned
unsigned long long reverse64Bit_with_16bitCache(unsigned long long x)
{
    const int kWordSize = 16;
    const int kBitMask = 0xFFFF;
    return  precomputed_reverse[x & kBitMask] << (3 * kWordSize) |
            precomputed_reverse[(x >> kWordSize) & kBitMask] << (2 * kWordSize) |
            precomputed_reverse[(x >> (2 * kWordSize)) & kBitMask] << kWordSize |
            precomputed_reverse[(x >> (3 * kWordSize)) & kBitMask];
}

//Read cache file and store it in the global array
void load_cache_to_array(std::string fileName)
{
    std::ifstream ipf(fileName);
    if(!ipf.is_open()) {
        std::cout << "Error opening file, map not created. Returning function call";
        return;
    }
        
    std::string sr;
    unsigned i = 0;
    while(ipf.good()) {
        std::getline(ipf, sr, '\n');
        unsigned long long reverse;
        if (sr != "")
        {
            reverse = std::stoull(sr, nullptr, 10);
            precomputed_reverse[i] = reverse;
        }
        ++i;
    }
    ipf.close();
}

//print array created from cache
void print_array()
{
    for(const auto &elem : precomputed_reverse)
        std::cout << elem << "\n";
}

//create a file and save all 16 bit numbers and its reverse
void calc_16Bit_reverse_cache_file(const unsigned x, const std::string &fileName)
{
    std::cout << "Creating file of reverse of bits of each of the 16 bit numbers\n";
    std::ofstream o(fileName);
    for (unsigned i = 0; i < x; i++) {
        o << reverse_kBits_Unsigned(i, 16) << "\n";
    }
    std::cout << "..Done";
}

//UNSIGNED VERSION : CREATING ONE MASK THEN XOR WITH X
unsigned long long reverse_kBits_Unsigned (unsigned long long x, const unsigned k)
{
    unsigned long long mask = 0;
    for(unsigned i = 0, j = k-1; i < j; ++i, --j)
    {
        if ( (x>>i & 1) != (x>>j & 1))
        {
            mask |= (1ULL<<i) | (1ULL<<j);
        }
    }
    x ^= mask;
    return x;
}

//SIGNED VERSION : CREATING ONE MASK THEN XOR WITH X
long long reverse_kBits_Signed (long long x, const unsigned k)
{
    long long mask = 0LL;
    for(unsigned i = 0, j = k-2; i < j; ++i, --j)
    {
        //std::cout << i << " " << j << endl;
        if ( (x>>i & 1) != (x>>j & 1))
        {
            mask |= (1LL<<i) | (1LL<<j);
            //std::cout << "   " << DNB(mask) << endl ;
            //std::cout << "x changed\n" << DNB(x) << "\n";
        }
    }
    x ^= mask;
    return x;
}
