#ifndef MURMURHASH_H
#define MURMURHASH_H

#include <cstdint>

class murmurhash {
public:
    murmurhash();

    uint32_t hash(int v) const;

private:
    uint32_t seed;
};

#endif
