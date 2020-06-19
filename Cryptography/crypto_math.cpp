#include "crypto_math.h"

namespace cyptoMath {

    long long int gcd(long long int a, long long int b, long long int& x, long long int& y)
    {
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

    int getMultiplBack(int a, int mod)
    {
        long long x, y;
        gcd(a, mod, x, y);
        if (x < 0)
            return mod + x;
        else
            return x;
    }

    bool PrimitiveRootGenerate(long g, long m)
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

    int GetPrimeRoot(long p)
    {
        for (long i = 1; i < p; i++)
        {
            if (PrimitiveRootGenerate(i, p))
                return i;
        }
        return 0;
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

    unsigned int GetNextPrime(unsigned int x)
    {
        static std::vector<unsigned int> cache;
        static unsigned int max_prime = 0;
        if (max_prime == 0) {
            cache.push_back(2);
            cache.push_back(3);
            max_prime = 3;
        }
        if (x >= max_prime) { // ��� � ����
            unsigned int limit = (x < 1000) ? 1024 : x / 4 * 5; // x+20%

            unsigned int start = max_prime + 2; // ������ ���� ������
            unsigned int* bitmap = (unsigned int*)calloc((limit - start) / 64 + 1, sizeof(unsigned int));
            limit -= start;

            if (max_prime > 3) { // ������������� ���������� ��������
                unsigned int* end = &cache[cache.size() - 1];
                for (unsigned int* cur = &cache[1]; cur <= end; cur++) {
                    unsigned int i = *cur * *cur;
                    if (i > limit + start) break;
                    unsigned int step = *cur << 1;
                    if (i < start) { // ������������ ��� cur*cur+2N*cur
                        i = start - (start - i) % step;
                        if (i < start) i += step;
                    }
                    i -= start;
                    //printf("start=%d i=%d max=%d\n", start, i, max_prime);
                    for (; i < limit; i += step) { // ����������� ������� max_prime
                        bitmap[i >> 6] |= (1 << ((i >> 1) & 31));
                    }
                }
            }

            bool need_fill = true;
            while (need_fill) {
                if (max_prime >= 65536 || max_prime * max_prime >= limit + start) {
                    need_fill = false; // ������ ��������� �� ����
                }
                else {
                    unsigned int step = max_prime << 1;
                    for (unsigned int i = max_prime * max_prime - start; i < limit; i += step) { // ����������� ������� max_prime
                        bitmap[i >> 6] |= (1 << ((i >> 1) & 31));
                    }
                }
                // ���������� �������� ������
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
            if (x == 0) { // ������������ ������
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
        else { // ����� � ����
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

}