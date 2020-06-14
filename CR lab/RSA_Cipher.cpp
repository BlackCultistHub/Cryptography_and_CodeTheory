#include <iostream>
#include "math.h"

int gcd(int a, int b, int& x, int& y) {
    if (a == 0) 
    {
        x = 0; y = 1;
        return b;
    }
    int x1 = 0, y1 = 0;
    int d = gcd(b % a, a, x1, y1);
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

int encript(int m, int e, int n)
{
    return modexp(m, e, n);
}
int decript(long int m, long int d, long int n)
{
    return modexp(m, d, n);
}
int RSAinit(int p, int q, int& e, int& n, int& d)
{
    int FermNumbers[5] = { 3, 5, 17, 257, 65537 };
    int f;
    int x = 0;
    int y = 0;
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

int main() 
{
    int x = 0, y = 0;
    int openExp, N, d;
    int p = 0,
        q = 0;
    int msg = 0;
    int encr = 0, decr;
    std::cout << "Please enter secret key:\n\tp(int) = ";
    std::cin >> p;
    std::cout << "\tq(int) = ";
    std::cin >> q;
    RSAinit(p, q, openExp, N, d);
    std::cout << "{SK} = {d(" << d << "),N(p(" << p << ")*q(" << q << "))}\t{PK} = {e(" << openExp << "),N(" << N << ")}" << std::endl;
    std::cout << "Please enter message to encrypt (int): ";
    std::cin >> msg;
    std::cout << "Encrypted = " << encript(msg, openExp, N) << std::endl;
    std::cout << "Please enter message to decrypt (int): ";
    std::cin >> encr;
    decr = decript(encr, d, N);
    std::cout << "Decrypted = " << decr << std::endl;
    system("pause");
    return 0;
}