#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include "../includes/HyperLogLog.h"
#include "../includes/MurmurHash.h"
using namespace hll;

#define hash_t uint64_t

void HyperLogLog::AddElem(std::string val) {
    mhash_64::MurmurHash mh;
    hash_t h = mh.hash(val);
    size_t register_index = h >> (64 - b), one_position = 64 - b;
    std::bitset<64> bin(h);
    for (size_t i = 64 - b; i >= 1; i--) {
        if (h & 1) one_position = i;
        h = h >> 1;
    }
    registers[register_index] = std::max(registers[register_index], one_position);
    std::cout << bin << " " << register_index << " " << one_position << " " << registers[register_index] << std::endl;
    cardinality = ComputeCardinality();
}

size_t HyperLogLog::ComputeCardinality() {
    double cardinality_temp;
    double sum = 0.0;
    for (size_t i = 0; i < m; i++) {
        sum += 1.0 / (1 << registers[i]);
    }
    cardinality_temp = hll_const / sum;
    double pow_2_64 = 18446744073709551616.0;
    double neg_pow_2_64 = -18446744073709551616.0;
    if (cardinality_temp <= 2.5 * m) {
        size_t zeroCnt = 0;
        for (size_t i = 0; i < m; i++) {
            if (registers[i] == 0) {
                zeroCnt++;
            }
        }
        if (zeroCnt != 0) {
            cardinality_temp = m * std::log((double)m / zeroCnt);
        }
    } else if (cardinality_temp > (1.0 / 30.0) * pow_2_64) {
        cardinality_temp = neg_pow_2_64 * log(1.0 - (cardinality_temp / pow_2_64));
    }
    return cardinality_temp;
}
