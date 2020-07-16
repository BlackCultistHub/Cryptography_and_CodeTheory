#pragma once

#include "crypto_math.h"

namespace RSA {

	typedef struct RSA_secret_keypair
	{
		RSA_secret_keypair(unsigned long long backExp, unsigned long long mod): d(backExp), N(mod) {}
		unsigned long long d;
		unsigned long long N;
	} RSA_secret_keypair;

	typedef struct RSA_open_keypair
	{
		RSA_open_keypair(unsigned long long exp, unsigned long long mod) : e(exp), N(mod) {}
		unsigned long long e;
		unsigned long long N;
	} RSA_open_keypair;

	unsigned long long int keyGen(unsigned long long int p, unsigned long long int q, unsigned long long int& e, unsigned long long int& n, unsigned long long int& d);

	unsigned long long int encript(unsigned long long int m, unsigned long long int e, unsigned long long int n);

	unsigned long long int decript(unsigned long long int m, unsigned long long int d, unsigned long long int n);

}