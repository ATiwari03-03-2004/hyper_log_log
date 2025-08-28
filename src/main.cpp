#include <iostream>
#include "../includes/HyperLogLog.h"
using namespace hll;

double eval_hll_const(size_t m) {
    double hll_const;
    switch (m) {
        case 16:
            hll_const = 0.673;
            break;
        case 32:
            hll_const = 0.697;
            break;
        case 64:
            hll_const = 0.709;
            break;
        default:
            hll_const = 0.7213 / (1.0 + (1.079 / m));
            break;
    }
    return hll_const * m * m;
}

int main() {
    size_t b;
    std::cout << "Enter no of leading bits: " << std::endl;
    std::cin >> b; 
    HyperLogLog _hll(b);
    _hll.hll_const = eval_hll_const(1ULL >> b);
    std::string val;
    std::cout << "\nMenu: " << std::endl;
    std::cout << "-----  " << std::endl;
    std::cout << "  1 Add an Element" << std::endl;
    std::cout << "  2 Get Cardinality" << std::endl;
    std::cout << "  -1 Exit\n" << std::endl;
    while (true) {
        int choice;
        std::cout << "\n> Enter your choice: " << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "\n> Enter the element: " << std::endl;
                std::cin >> val;
                _hll.AddElem(val);
                break;
            case 2:
                std::cout << "\n  Cardinality: " << _hll.GetCardinality() << std::endl;
                break;
            case -1:
                std::cout << "\n Exit success...\n" << std::endl;
                exit(0);
                break;
            default:
                std::cout << "\n Invalid choice!" << std::endl;
                break;
        }
    }
    return 0;
}
