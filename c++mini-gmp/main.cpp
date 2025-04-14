#define MAIN_CPP

#include <iostream>
#include <cstdint>
#include <string>
#include "gmp/mini-gmp.c"
#include "gmp/mini-gmp.h"
#include "gmp/mini-gmpxx.h"

#include "irrationals.hpp"
#include "frac.cpp"

typedef int64_t int_t;

int cfaSimple(Frac a, int_t n, int_t* c_list) {
    mpz_class c;
    Frac r;
    r = a;
    for (int_t i = 0; i < n; i++) {
        c = r.num / r.den;
        c_list[i] = c.get_ui();
        
        r.num -= c * r.den;
        
        if (mpz_cmp_si(r.num.get_mpz_t(), 0) == 0) {
            return i + 1;
        }   
        mpz_swap(r.num.get_mpz_t(), r.den.get_mpz_t());
    }
    return n;    
}

int cfaStop(RationalRange aRange, int_t n, int_t* c_list) {
    mpz_class c1, c2;
    Frac r1, r2;

    r1 = aRange.lo;
    r2 = aRange.hi;
    
    for (int_t i = 0; i < n; i++) {
        c1 = r1.num / r1.den;
        c2 = r2.num / r2.den;
        if (c1 != c2) {
            return i;
        }
        
        c_list[i] = c1.get_ui();

        r1.num -= c1 * r1.den;
        r2.num -= c1 * r2.den;

        if (mpz_sgn(r1.num.get_mpz_t()) == 0 || mpz_sgn(r2.num.get_mpz_t()) == 0) {
            return i + 1;
        }
        
        mpz_swap(r1.num.get_mpz_t(), r1.den.get_mpz_t());
        mpz_swap(r2.num.get_mpz_t(), r2.den.get_mpz_t());
    }
    return n;    
}



int main() {
    std::string number_string = PI;
    
    RationalRange aRange = decToRRange(number_string, -1);

    std::cout << "Alpha Approximation: " << aRange.lo.num.get_str() << " / " << aRange.lo.den.get_str() << "\n" << std::endl;

    int_t n = 1000;
    int_t c_list[n];

    int_t length = cfaStop(aRange, n, c_list);

    std::cout << "c list (count: " << std::to_string(length) << ") = \n" << std::to_string(c_list[0]);
    for (int_t i = 1; i < length; i++) {
        std::cout << ", " << std::to_string(c_list[i]);
    }
    std::cout << "\n" << std::endl;


    Frac approx = cListToFrac(length, c_list);
    std::cout << "p / q = \n" << approx.num.get_str() << " / " << approx.den.get_str() << "\n" << std::endl;

    Frac dif;
    dif.num = aRange.lo.num * approx.den - approx.num * aRange.lo.den;
    dif.den = approx.den * aRange.lo.den;

    mpz_abs(dif.num.get_mpz_t(), dif.num.get_mpz_t());

    std::cout << "a - p / q = " << divideFraction(dif, 10) << "\n" << std::endl;
    

    /*
    int_t n_frac = 1000;
    Frac fractions[n_frac];
    int_t length_frac = cListToFracList(length, c_list, n_frac, fractions);
    for (int_t i = 0; i < length_frac; i++) {
        std::cout << fractions[i].num.get_str() << " / " << fractions[i].den.get_str() << ", ";
    }
    std::cout << "\n" << std::endl;
    */
    
    return 0;
}