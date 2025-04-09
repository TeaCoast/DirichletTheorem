#include <iostream>
#include <cstdint>
#include <string>
#include "gmp/mini-gmp.c"
#include "gmp/mini-gmp.h"
#include "gmp/mini-gmpxx.h"

int main() {
    mpz_class a = 123456789;
    std::string str = "98765432109876543210";
    mpz_class b(str);
    mpz_class c = a + b;

    std::cout << "Value: " << c.get_str() << std::endl;

    mpq_class frac(5, 2);

    std::cout << "Fraction: " << frac.get_str() << std::endl;
    
    return 0;
}