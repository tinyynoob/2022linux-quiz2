#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define ITER 100

static size_t naive(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    for (size_t k = 0; k < bitmapsize; ++k) {
        uint64_t bitset = bitmap[k];
        size_t p = k * 64;
        for (int i = 0; i < 64; i++) {
            if ((bitset >> i) & 0x1)
                out[pos++] = p + i;
        }
    }
    return pos;
}

static size_t improved(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t t = 1ul << __builtin_ctzll(bitset);
            int r = __builtin_ctzll(bitset);
            out[pos++] = k * 64 + r;
            bitset ^= t;
        }
    }
    return pos;
}

static inline void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

static uint64_t gen_bm(int set_num)
{
    int array[64];
    for (int i = 0; i < 64; i++)
        array[i] = i;
    for (int i = 0; i < set_num; i++)  // flush
        swap(&array[i], &array[rand() % 64]);
    uint64_t ans = 0;
    for (int i = 0; i < set_num; i++)  // add set bits
        ans ^= 1ul << array[i];
    return ans;
}

int main(int argc, char *argv[])
{
    const int weight = atoi(argv[1]);
    srand(time(NULL));

    unsigned long long total_nai = 0, total_imp = 0;
    for (int i = 0; i < ITER; i++) {
        uint64_t bitmap[SIZE];
        for (int j = 0; j < SIZE; j++)
            bitmap[j] = gen_bm(weight);

        struct timespec t1, t2, t3;
        uint32_t out[SIZE * 64];
        clock_gettime(CLOCK_MONOTONIC, &t1);
        naive(bitmap, SIZE, out);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        improved(bitmap, SIZE, out);
        clock_gettime(CLOCK_MONOTONIC, &t3);

        total_nai += (unsigned long long) (t2.tv_sec * 1e9 + t2.tv_nsec) -
                     (t1.tv_sec * 1e9 + t1.tv_nsec);
        total_imp += (unsigned long long) (t3.tv_sec * 1e9 + t3.tv_nsec) -
                     (t2.tv_sec * 1e9 + t2.tv_nsec);
        printf("%d,%llu,%llu\n", (i + 1) * SIZE, total_nai, total_imp);
    }
    return 0;
}
