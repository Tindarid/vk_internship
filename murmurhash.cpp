#include "murmurhash.h"
#include <ctime>
#include <cstdlib>

murmurhash::murmurhash() {
    srand(time(NULL));
    seed = rand();
}

uint32_t murmurhash::hash(int key) const {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    int len = sizeof(int);
    uint32_t h = seed ^ len;

    const uint32_t* data = (const uint32_t*)(&key);

    for (; len >= 4; data += 4, len -= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;
    }

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
} 
