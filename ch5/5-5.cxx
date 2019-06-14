typedef unsigned us;

#include <bits/stdc++.h>
#define bs (bitset<8>)
#define DNB(a) std::setw(3) << (a) << " : " << bitset<8>(a)
using namespace std;

us add (us a, us b)
{
        while (b) {
                us carry = a&b;
                cout << DNB(a) << "\n" << DNB(b) << "   " << DNB(carry) << "\n----------------\n";
                a = a^b;
                b = carry << 1;
        }
        return a;
}

int main(int argc, char **argv)
{
        cout << add(7,5);
	
	return 0;
}