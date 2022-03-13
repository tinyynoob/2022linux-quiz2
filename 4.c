#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

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
            uint64_t t = 1u << __builtin_ctzll(bitset);
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
    printf("weight = %d\n", weight);
    srand(time(NULL));

    uint64_t bitmap[SIZE];
    uint32_t out[SIZE * 2];
    for (int i = 0; i < SIZE; i++)
        bitmap[i] = gen_bm(weight);

    return 0;
}
