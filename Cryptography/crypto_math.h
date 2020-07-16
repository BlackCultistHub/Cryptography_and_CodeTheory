#pragma once

#include <vector>

namespace cryptoMath {

	bool getBit(unsigned long long code, unsigned int pointer); //pointer [0 - n]

	long long int gcd(long long int a, long long int b, long long int& x, long long int& y);

	unsigned long long int modexp(unsigned long long number, unsigned long long degree, unsigned long long mod);

	unsigned long long getMultiplBack(unsigned long long a, unsigned long long mod);

	bool PrimitiveRootGenerate(long g, long m);

	int GetPrimeRoot(long p);

	unsigned long long superDuperHashFunction(unsigned long long msg, unsigned long long salt = 0, unsigned long long module = 3715, int difficulty = 13);

	unsigned int GetNextPrime(unsigned int x);
}