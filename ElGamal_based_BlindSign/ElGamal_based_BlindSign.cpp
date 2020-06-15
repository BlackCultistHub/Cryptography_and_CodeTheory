//#include "stdafx.h"
#include "math.h"
#include <string>
#include <iostream>
#include <vector>
#include "sha-256.h"

unsigned int next_prime(unsigned int x)
{
    static std::vector<unsigned int> cache;
    static unsigned int max_prime = 0;
    if (max_prime == 0) {
        cache.push_back(2);
        cache.push_back(3);
        max_prime = 3;
    }
    if (x >= max_prime) { // нет в кэше
        unsigned int limit = (x < 1000) ? 1024 : x / 4 * 5; // x+20%

        unsigned int start = max_prime + 2; // должно быть четное
        unsigned int* bitmap = (unsigned int*)calloc((limit - start) / 64 + 1, sizeof(unsigned int));
        limit -= start;

        if (max_prime > 3) { // инициализация предыдущим расчетом
            unsigned int* end = &cache[cache.size() - 1];
            for (unsigned int* cur = &cache[1]; cur <= end; cur++) {
                unsigned int i = *cur * *cur;
                if (i > limit + start) break;
                unsigned int step = *cur << 1;
                if (i < start) { // выравнивание под cur*cur+2N*cur
                    i = start - (start - i) % step;
                    if (i < start) i += step;
                }
                i -= start;
                //printf("start=%d i=%d max=%d\n", start, i, max_prime);
                for (; i < limit; i += step) { // Вычеркиваем кратные max_prime
                    bitmap[i >> 6] |= (1 << ((i >> 1) & 31));
                }
            }
        }

        bool need_fill = true;
        while (need_fill) {
            if (max_prime >= 65536 || max_prime * max_prime >= limit + start) {
                need_fill = false; // дальше заполнять не надо
            }
            else {
                unsigned int step = max_prime << 1;
                for (unsigned int i = max_prime * max_prime - start; i < limit; i += step) { // Вычеркиваем кратные max_prime
                    bitmap[i >> 6] |= (1 << ((i >> 1) & 31));
                }
            }
            // вычитываем следущую порцию
            for (unsigned int i = max_prime + 2 - start; i < limit; i += 2) {
                if ((bitmap[i >> 6] & (1 << ((i >> 1) & 31))) == 0) {
                    cache.push_back(i + start);
                    if (need_fill) {
                        break;
                    }
                }
            }
            max_prime = cache.back();
        }
        free(bitmap);
    }

    static unsigned int prev_id = 0;
    static unsigned int prev_prime = 0;
    if (x < 2) {
        if (x == 0) { // освобождение памяти
            max_prime = 0;
            cache.clear();
        }
        prev_id = 0;
        prev_prime = 2;
    }
    else if (x == prev_prime) {
        prev_id++;
        prev_prime = cache[prev_id];
    }
    else { // поиск в кэше
        unsigned int* min = &cache[0];
        unsigned int* max = &cache[cache.size() - 1];
        while (max - min > 1) {
            unsigned int* mid = min + (max - min) / 2;
            if (*mid > x) {
                max = mid;
            }
            else {
                min = mid;
            }
        }
        prev_id = max - &cache[0];
        prev_prime = *max;
    }
    return prev_prime;
}

unsigned int getRandomPls(int up)
{
    return rand() + up;
}

long long int modexp(long long int x, long long int y, long long int N) // x^y mod N for big numbers (<= 8byte)
{
    if (y == 0) return 1;
    long long int z = modexp(x, y / 2, N);
    if (y % 2 == 0)
        return (z * z) % N;
    else
        return (x * z * z) % N;
}

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

int getMultiplBack(int a, int mod)
{
    int x, y;
    gcd(a, mod, x, y);
    if (x < 0)
        return mod + x;
    else
        return x;
}

bool PrimitiveRoot(long g, long m)
{
    long phi = m - 1; // Eyler func

    for (long i = 1; i < phi; i++)
    {
        long num = modexp(g, i, m);
        if (num == 1)
            return false;
    }
    return true;
}

int PrimeRootGen(long p)
{
    for (long i = 1; i < p; i++)
    {
        if (PrimitiveRoot(i, p))
            return i;
    }
    return 0;
}

void InitELGamal(long& x, long& y, long& p, long& g)
{
    g = PrimeRootGen(p);
    if (x > p - 1 || x <= 1)
    {
        throw "Secret key x is out of range (1 < x < p-1). Please try again.";
    }
    y = modexp(g,x,p);
}

long long superDuperHashFunction(long long msg, long long salt = 0, long module = 3715, int difficulty = 13)
{
    for (int i = 0; i < difficulty; i++)
    {
        msg += salt + i;
        msg %= module;
    }
    return msg;
}

int main()
{
    try
    {
        long x = 157, y = 0;
        long p = next_prime(getRandomPls(50000)), g = 0;
        long msg = 101, salt = 12345;

        //-----[ 1 ]-----
        std::cout << "Enter secret X (long): ";
        std::cin >> x;
        InitELGamal(x, y, p, g);
        std::cout << "{SK} = {c(" << x << ")} {PK} = {p(" << p << "), g(" << g << "), y(" << y << ")}" << std::endl;
        //-----[ 2 ]-----
        std::cout << "Enter message (long): ";
        std::cin >> msg;
        std::cout << "Enter salt (long): ";
        std::cin >> salt;
        //-----[ 3 ]-----
        long long saltedMsg = msg + salt + y;
        std::cout << "Salted with salt and {PK}: " << saltedMsg << std::endl;
        long long hashedMsg = superDuperHashFunction(saltedMsg);
        std::cout << "Hashed salted msg: " << hashedMsg << std::endl;
        //-----[ 4 ]-----
        long k = next_prime(getRandomPls(45000));
        long r = modexp(g, k, p);
        long long mins = hashedMsg - x * r;
        long s = 0;
        if (mins < 0)
            while (mins <= 0)
                mins += p - 1;
        s = mins * getMultiplBack(k, p - 1) % (p - 1);
        std::cout << "{SIGN} = {r(" << r << "), s(" << s << ")}" << std::endl;
        //-----[ 5 ]-----
        std::cout << "Transfered:\n" <<
            "====================\n" <<
            "Message(" << msg << "),\n" <<
            "Salt(" << salt << "),\n" <<
            "{SIGN} = { r(" << r << "), s(" << s << ")},\n" <<
            "{PK} = {p(" << p << "), g(" << g << "), y(" << y << ")}\n" << 
            "====================" << std::endl;
        long long unsaltedMsg = msg + salt + y;
        std::cout << "Unsalted with salt and {PK}: " << unsaltedMsg << std::endl;
        long long RhashedMsg = superDuperHashFunction(saltedMsg);
        std::cout << "Hashed unsalted msg: " << RhashedMsg << std::endl;
        //-----[ 6 ]-----
        std::cout << "Checking sign..." << std::endl;
        //1. check r/s
        if (r <= 0 || r >= p)
            throw "Sign check failed by checking r.";
        std::cout << "r-value OK." << std::endl;
        if (s <= 0 || s >= p - 1)
            throw "Sign check failed by checking s.";
        std::cout << "s-value OK." << std::endl;
        //2. checking math
        if (modexp(y, r, p) * modexp(r, s, p) % p!= modexp(g, RhashedMsg, p))
            throw "Sign check failed by math check.";
        std::cout << "Math OK." << std::endl;
        std::cout << "{SIGN} OK!" << std::endl;
        return 0;
    }
    catch (const char* exception)
    {
        std::cout << "\n=====[ EXCEPTION ]=====" << std::endl;
        std::cout << exception << std::endl;
        std::cout << "=======================" << std::endl;
        return -1;
    }
}