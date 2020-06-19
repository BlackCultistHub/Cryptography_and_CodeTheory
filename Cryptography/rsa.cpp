#include "rsa.h"

namespace RSA {

    long long int keyGen(long long int p, long long int q, long long int& e, long long int& n, long long int& d)
    {
        int FermNumbers[5] = { 3, 5, 17, 257, 65537 };
        long long int f;
        long long int x = 0;
        long long int y = 0;
        f = (p - 1) * (q - 1); //n eyler function 
        n = p * q;
        for (int i = 4; i >= 0; i--)
        {
            if (FermNumbers[i] < f)
            {
                e = FermNumbers[i];
                break;
            }
        }
        if (e > f || cryptoMath::gcd(e, f, x, y) != 1)
        {
            //printf("error");
            return -1;
        }
        x = 0;
        y = 0;
        cryptoMath::gcd(e, f, x, y);
        if (x < 0)
            d = f + x;
        else
            d = x;
        return 0;
    }

    long long int encript(long long int m, long long int e, long long int n)
    {
        return cryptoMath::modexp(m, e, n);
    }

    long long int decript(long long int m, long long int d, long long int n)
    {
        return cryptoMath::modexp(m, d, n);
    }

}