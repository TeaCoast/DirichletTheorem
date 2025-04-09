#include <iostream>
#include <cstdint>
#include <string>
#include "gmp.h"
#include "gmpxx.h"
#include "pi.hpp"

typedef int64_t int_t;

int main() {
    mpq_class fraction(0, 5);

    std::cout << "Value: " << fraction.get_str() << std::endl;

    bool is_zero = mpq_sgn(fraction.get_mpq_t()) == 0;

    std::cout << "Bool: " << is_zero << std::endl;
}