#include "rsa.h"

namespace RSA {

    unsigned long long int keyGen(unsigned long long int p, unsigned long long int q, unsigned long long int& e, unsigned long long int& n, unsigned long long int& d)
    {
        int FermNumbers[5] = {65537, 257, 17, 5, 3};
        unsigned long long int f;
        long long int x = 0;
        long long int y = 0;
        f = (p - 1) * (q - 1); //n eyler function 
        n = p * q;
        for (int i = 0; i < 5; i++)
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

    unsigned long long int encript(unsigned long long int m, unsigned long long int e, unsigned long long int n)
    {
        return cryptoMath::modexp(m, e, n);
    }

    unsigned long long int decript(unsigned long long int m, unsigned long long int d, unsigned long long int n)
    {
        return cryptoMath::modexp(m, d, n);
    }

}