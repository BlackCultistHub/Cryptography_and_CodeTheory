#pragma once

#include <vector>

namespace cryptoMath {

	long long int gcd(long long int a, long long int b, long long int& x, long long int& y);

	long long int modexp(long long int x, long long int y, long long int N);

	int getMultiplBack(int a, int mod);

	bool PrimitiveRootGenerate(long g, long m);

	int GetPrimeRoot(long p);

	long long superDuperHashFunction(long long msg, long long salt = 0, long module = 3715, int difficulty = 13);

	unsigned int GetNextPrime(unsigned int x);
}