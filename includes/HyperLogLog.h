#include <iostream>
#include <vector>
#include <cstdint>

#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

namespace hll {
    class HyperLogLog {
    private:
        

    public:
        HyperLogLog() {}

        std::vector<uint64_t> get_blocks(std::string& input);

        uint64_t hash(std::string& input);
    };
}

#endif
