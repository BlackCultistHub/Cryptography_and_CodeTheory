#include <iostream>
#include "math.h"

long long int gcd(long long int a, long long int b, long long int& x, long long int& y) {
    if (a == 0) 
    {
        x = 0; y = 1;
        return b;
    }
    long long int x1 = 0, y1 = 0;
    long long int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
long long int modexp(long long int x, long long int y, long long int N)
{
    if (y == 0) return 1;
    long long int z = modexp(x, y / 2, N);
    if (y % 2 == 0)
        return (z * z) % N;
    else
        return (x * z * z) % N;
}

long long int encript(long long int m, long long int e, long long int n)
{
    return modexp(m, e, n);
}
long long int decript(long long int m, long long int d, long long int n)
{
    return modexp(m, d, n);
}
long long int RSAinit(long long int p, long long int q, long long int& e, long long int& n, long long int& d)
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
    if (e > f || gcd(e, f, x, y) != 1)
    {
        printf("error");
        return -1;
    }
    x = 0;
    y = 0;
    gcd(e, f, x, y);
    if (x < 0)
        d = f + x;
    else
        d = x;
    return 0;
}

void kill(int N, int msg)
{
    unsigned int limit = N - msg;
    for (int i = 0; i < limit; i++)
    {
        long double* r = new long double[msg / 2];
        for (int k = 0; k < limit; k++)
        {
            std::cout << "YOU WILL BE PUNISHED!!!YOU WILL BE PUNISHED!!!YOU WILL BE PUNISHED!!!\n";
            long double* r = new long double[msg / 4];
            //char* little = new char[10];
            for (int j = 0; j < msg / 4; j++)
            {
                r[j] = msg;
            }
            //free(little);
        }
    }
}

int main() 
{
    long long int x = 0, y = 0;
    long long int openExp, N, d;
    long long int p = 0,
        q = 0;
    long long int msg = 0;
    long long int encr = 0, decr;
    std::cout << "Please enter secret key:\n\tp(int) = ";
    std::cin >> p;
    std::cout << "\tq(int) = ";
    std::cin >> q;
    RSAinit(p, q, openExp, N, d);
    std::cout << "{SK} = {d(" << d << "),N(p(" << p << ")*q(" << q << "))}\t{PK} = {e(" << openExp << "),N(" << N << ")}" << std::endl;
    std::cout << "Please enter message to encrypt (int): ";
    std::cin >> msg;
    if (msg > N)
        kill(N, msg);
    std::cout << "Encrypted = " << encript(msg, openExp, N) << std::endl;
    std::cout << "Please enter message to decrypt (int): ";
    std::cin >> encr;
    decr = decript(encr, d, N);
    std::cout << "Decrypted = " << decr << std::endl;
    system("pause");
    return 0;
}