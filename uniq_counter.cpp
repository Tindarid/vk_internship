#include "uniq_counter.h"
#include <algorithm>
#include <cmath>
#include <cassert>

uniq_counter::uniq_counter() : uniq_counter(DEFAULT_BYTES) { }

uniq_counter::uniq_counter(int b) {
    assert(b >= MIN_BYTES && b <= MAX_BYTES);

    bytes = b;
    size = 1 << bytes;
    buckets = new uint8_t[size]();

    switch (size) {
        case 16:
            alpha = 0.673;
            break;
        case 32:
            alpha = 0.697;
            break;
        case 64:
            alpha = 0.709;
            break;
        default:
            alpha = 0.7213 / (1 + 1.079 / size);
            break;
    }
}

uniq_counter::~uniq_counter() {
    delete[] buckets;
}

void uniq_counter::add(int v) {
    uint32_t h = hasher.hash(v);
    uint32_t j = h >> (DWORD - bytes);
    uint32_t w = h << bytes;
    buckets[j] = std::max(buckets[j], rank(w));
}

int uniq_counter::get_uniq_num() const {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(2.0, -buckets[i]);
        if (!buckets[i]) {
            count++;
        }
    }
    double res = alpha * size * size / sum;
    if (res <= size * 2.5 && count) {
        res = size * log(1.0 * size / count);
    }
    double temp = pow(2.0, DWORD);
    if (res > temp / 30) {
        res = -temp * log(1 - res / temp);
    }
    return res;
}

uint8_t uniq_counter::rank(uint32_t v) const {
    uint8_t count = 0;
    while (v != 0) {
        v >>= 1;
        count++;
    }
    return DWORD - count + 1;
}
