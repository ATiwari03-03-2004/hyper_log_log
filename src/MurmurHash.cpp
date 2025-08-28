#include <iostream>
#include <vector>
#include "../includes/MurmurHash.h"
using namespace mhash_64;

std::vector<uint64_t> MurmurHash::get_blocks(std::string& input) {
    std::vector<uint64_t> blocks;
    for (size_t i = 0; i < (input.size() - (input.size() % 8)); i += 8) {
        uint64_t block = 0;
        block |= (uint64_t)(uint8_t)input[i] << 0;
        block |= (uint64_t)(uint8_t)input[i + 1] << 8;
        block |= (uint64_t)(uint8_t)input[i + 2] << 16;
        block |= (uint64_t)(uint8_t)input[i + 3] << 24;
        block |= (uint64_t)(uint8_t)input[i + 4] << 32;
        block |= (uint64_t)(uint8_t)input[i + 5] << 40;
        block |= (uint64_t)(uint8_t)input[i + 6] << 48;
        block |= (uint64_t)(uint8_t)input[i + 7] << 56;
        blocks.push_back(block);
    }
    return blocks;
}

uint64_t MurmurHash::hash(std::string& input) {
    uint64_t hash = seed ^ (input.size() * m);
    std::vector<uint64_t> blocks = get_blocks(input);
    for (size_t i = 0; i < blocks.size(); i++) {
        uint64_t k = blocks[i];
        k *= m;
        k ^= k >> r;
        k *= m;
        hash ^= k;
        hash *= m;
    }
    switch (input.size() % 8) {
        case 7: hash ^= uint64_t(input[input.size() - 7]) << 48;
        case 6: hash ^= uint64_t(input[input.size() - 6]) << 40;
        case 5: hash ^= uint64_t(input[input.size() - 5]) << 32;
        case 4: hash ^= uint64_t(input[input.size() - 4]) << 24;
        case 3: hash ^= uint64_t(input[input.size() - 3]) << 16;
        case 2: hash ^= uint64_t(input[input.size() - 2]) << 8;
        case 1: hash ^= uint64_t(input[input.size() - 1]); hash *= m;
    }
    hash ^= hash >> r;
    hash *= m;
    hash ^= hash >> r;
    return hash;
}
