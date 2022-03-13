#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define min(x, y)          \
    ({                     \
        typeof(x) _x = x;  \
        typeof(y) _y = y;  \
        _x < _y ? _x : _y; \
    })

static uint64_t gcd64_ori(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;
    int shift;
    for (shift = 0; !((u | v) & 1); shift++) {
        u /= 2, v /= 2;
    }
    while (!(u & 1))
        u /= 2;
    do {
        while (!(v & 1))
            v /= 2;
        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while ((v != 1) && (v != 0));
    return u << shift;
}

static uint64_t gcd64_imp(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;
    int shift = min(__builtin_ctz(u), __builtin_ctz(v));

    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while ((v != 1) && (v != 0));
    return u << shift;
}

int main()
{
    FILE *f;
    switch (1) {  // set this to choose cases
    case 0:
        f = fopen("small_num.txt", "r");
        printf("measure for small cases...\n");
        break;
    case 1:
        f = fopen("big_num.txt", "r");
        printf("measure for big cases...\n");
        break;
    default:
        f = fopen("RNG.txt", "r");
        printf("measure for custom cases...\n");
    }

    FILE *f_out = fopen("gcd_time.csv", "w");
    uint64_t totaltime_ori = 0, totaltime_imp = 0;  // time summation
    uint64_t a, b;
    unsigned counter = 0;
    while (fscanf(f, "%lu %lu", &a, &b) != EOF) {
        uint64_t ans_ori, ans_imp;
        struct timespec t1, t2, t3;
        clock_gettime(CLOCK_MONOTONIC, &t1);
        ans_ori = gcd64_ori(a, b);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        ans_imp = gcd64_imp(a, b);
        clock_gettime(CLOCK_MONOTONIC, &t3);

        totaltime_ori += (uint64_t)(t2.tv_sec * 1e9 + t2.tv_nsec) -
                         (t1.tv_sec * 1e9 + t1.tv_nsec);
        totaltime_imp += (uint64_t)(t3.tv_sec * 1e9 + t3.tv_nsec) -
                         (t2.tv_sec * 1e9 + t2.tv_nsec);
        fprintf(f_out, "%u,%lu,%lu\n", ++counter, totaltime_ori, totaltime_imp);
    }
    printf("User space total consumption time over %u pairs:\n", counter);
    printf("original : %lu (ns)\n", totaltime_ori);
    printf("improved : %lu (ns)\n", totaltime_imp);
    fclose(f_out);
    fclose(f);
    return 0;
}