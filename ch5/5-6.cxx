//Compute x/y (no floating values) without '/' arithmetic operator
#include <iostream>
#include <bitset>
#include <iomanip>
#define DNB(a) std::cout << std::setw(3) << (a) << " : " << std::bitset<64>(a) << "\n"

/*
    power   : 'k'         | used to add (2_pow_k) to the result(quotient), [(2_pow_k)   == (1 << k)]
    y_power : (2_pow_k)*y | subtract it from dividend in each iteration,   [(2_pow_k)*y == (y << k)]
*/
unsigned divide(unsigned x, unsigned y)
{
    unsigned result = 0;                                                      //quotient
    unsigned power = 32;                                                      //dealing with 32 bit words
    unsigned long long y_power = static_cast<unsigned long long>(y) << power; //shift y 32 bits left
    DNB(y_power);
    while (x >= y)
    { //loop till x becomes less than equals to y
        while (y_power > x) //aim is to find first (2_pow_k)*y greater than x
        {
            y_power >>= 1; //keep shifting y_power left till it becomes less than or equals to x | (2_pow_k)*y -> (2_pow_k-1)*y -> (2_pow_k-2)...
            --power;       //reduce power
        }
        result += 1U << power; //add 2_pow_power to the result(quotient)
        x -= y_power;          //reduce x by y_power || subtract (2_pow_k)*y from x
        std::cout << power << "\n";
        DNB(y_power) << "\t" << "quotient : "; DNB(result);
    }
    return result;
}

int main(int argc, char const *argv[])
{
    std::cout << divide(300, 20);
    return 0;
}
