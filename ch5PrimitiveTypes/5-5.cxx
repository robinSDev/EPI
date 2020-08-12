typedef unsigned us;

#include <bits/stdc++.h>
#define bs (bitset<8>)
#define DNB(a) std::setw(3) << (a) << " : " << bitset<8>(a)
using namespace std;

us add(us a, us b)
{
	while (b)
	{
		us carry = a & b;
		//cout << DNB(a) << "\n" << DNB(b) << "   AND:(future 'b' << 1): " << DNB(carry) << "\nXOR(future 'a')\n----------------\n";
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}
/*Add '2_pow_k * y' (left shift y by k) to result if kth bit of x is set  */
us multiply(us x, us y)
{
	us sum = 0;
	while (x) //for every set bit in 'x', add y to sum
	{
		if (x & 1)
			sum = add(sum, y);
		x >>= 1; //shift 'x' one bit to right, to access each bit
		y <<= 1; //shift 'y' one bit to left to maintain k, just to add 2_pow_k*y to result when kth bit of x is set
	}
	return sum;
}

int main(int argc, char **argv)
{
	//cout << add(7, 5);
	cout << multiply(7, 5);
	return 0;
}