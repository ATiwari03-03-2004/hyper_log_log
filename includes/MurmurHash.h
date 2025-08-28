#include <iostream>
#include <vector>
#include <cstdint>

#ifndef MURMURHASH_H
#define MURMURHASH_H

namespace mhash_64 {
    class MurmurHash {
    private:
        const uint64_t m;
        const int r;
        const int seed;

    public:
        MurmurHash() : m(0xc6a4a7935bd1e995), r(47), seed(12345) {}

        std::vector<uint64_t> get_blocks(std::string& input);

        uint64_t hash(std::string& input);
    };
}

#endif
