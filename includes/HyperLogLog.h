#include <iostream>
#include <vector>
#include <cmath>

#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

namespace hll {
    class HyperLogLog {
    private:
        size_t b; // intial leading bits of the hash, to be used for accessing the buckets/registers
        size_t m; // size of buckets/registers
        std::vector<size_t> registers;
        size_t cardinality;

    public:
        double hll_const;

    public:
        HyperLogLog(size_t inital_bits) : b(inital_bits), m(1ULL << b), registers(m, 0), cardinality(0), hll_const(0.0) {}

        size_t GetCardinality() { return cardinality; }

        void AddElem(std::string val);

        size_t ComputeCardinality();
    };
}

#endif
