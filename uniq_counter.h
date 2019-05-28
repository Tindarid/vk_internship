#ifndef UNIQ_COUNTER_H
#define UNIQ_COUNTER_H

#include "murmurhash.h"

class uniq_counter {
public:
    uniq_counter();
    uniq_counter(int);
    ~uniq_counter();

    void add(int);
    int get_uniq_num() const;

private:
    const static int DWORD = 32;
    const static int MIN_BYTES = 4;
    const static int MAX_BYTES = 16;
    const static int DEFAULT_BYTES = 15;

    murmurhash hasher;
    int bytes;
    int size;
    double alpha;
    uint8_t* buckets;

    uint8_t rank(uint32_t) const;
};

#endif
