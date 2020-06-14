//#include "stdafx.h"
#include "math.h"

#define RAND_PRIMAL 65537
#define ERROR_OK 0
#define ERROR_BAD_X 1

//сообщение соль 2 байта
int degree(long a, long b) // функци€ дл€ возведени€ числа в степень
{
    int sum = 1;
    for (int i = 0; i < b; i++)
        sum *= a;
    return sum;
}

int func_phi(long n) // функци€ Ёйлера
{
    long ret = 1;
    for (long i = 2; i * i <= n; ++i) {
        long p = 1;
        while (n % i == 0) {
            p *= i;
            n /= i;
        }
        if ((p /= i) >= 1) ret *= p * (i - 1);
    }
    return --n ? n * ret : ret;
}

bool PrimitiveRoot(long g, long m)
{
    long phi = func_phi(m);

    char* arr = new char[phi];
    long size = 0;
    bool b = true;

    for (long i = 0; (i <= phi - 1 && b); i++)
    {
        long num = (degree(g, i) % m);
        for (int u = 0; u < size; u++)
        {
            if (arr[u] == num)
                b = false;
        }
        arr[size] = num;
        size++;
    }
    return b;
}
int PrimeRootGen(long p)
{
    for (long i = 0; i < p; i++)
    {
        if (PrimitiveRoot(i, p))
        {
            return i;
        }
    }
    return 0;
}

int InitELGamal(long& x, long& y)
{
    long p = RAND_PRIMAL;
    long g = PrimeRootGen(p);
    if (x > p - 1)
    {
        return ERROR_BAD_X;
    }
    y = (long)pow(g, x) % p;
    return ERROR_OK;
}
int MessageAndSaultInput(long& m, long& s)
{
    scanf("%d", m);
    scanf("%d", s);
    return ERROR_OK;
}
int ApplySaultAndHash(long& saultedMasage, long& m, long& s)
{

    saultedMasage = m << 16;
    saultedMasage = saultedMasage + s;
    // TODO add hash

}
int elGamalsign(long& signedMessage, long& unsignedMessage)
{
}
int main()
{
    return 0;
}