#pragma once

#include "crypto_math.h"

namespace RSA {

	typedef struct RSA_secret_keypair
	{
		RSA_secret_keypair(long long backExp, long long mod): d(backExp), N(mod) {}
		long long d;
		long long N;
	} RSA_secret_keypair;

	typedef struct RSA_open_keypair
	{
		RSA_open_keypair(long long exp, long long mod) : e(exp), N(mod) {}
		long long e;
		long long N;
	} RSA_open_keypair;

	long long int keyGen(long long int p, long long int q, long long int& e, long long int& n, long long int& d);

	long long int encript(long long int m, long long int e, long long int n);

	long long int decript(long long int m, long long int d, long long int n);

}