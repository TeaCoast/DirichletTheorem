#ifndef APPROX_CPP
#define APPROX_CPP

#ifndef MAIN_CPP
#define MAIN_CPP
#define APPROX_CPP_MAIN
#endif

#include <iostream>
#include <cstdint>
#include <string>
#include "gmp/mini-gmp.c"
#include "gmp/mini-gmp.h"
#include "gmp/mini-gmpxx.h"

#include "frac.cpp"

Frac approxE_CompoundInterest(int_t n) {
    Frac e = {n + 1, n};
    mpz_pow_ui(e.num.get_mpz_t(), e.num.get_mpz_t(), n);
    mpz_pow_ui(e.den.get_mpz_t(), e.den.get_mpz_t(), n);
    return e;
}

// 2 1 2 1 1 4 1 1 6 1 1 8 1 1 10 1 1 12

Frac approxE_ContinuedFraction(int_t n) {
    int_t c_even = (n - 1) / 3 * 2 + 2;
    int_t c;
    if (n == 1) {
        c = 2;
    }
    else if ((n - 1) % 3 == 2) {
        c_even -= 2;
        c = c_even;
    } else {
        c = 1;
    }
    
    Frac approx = {c, 1};
    for (int_t i = n - 2; i >= 0; i--) {
        if (i == 0) {
            c = 2;
        }
        else if (i % 3 == 2) {
            c_even -= 2;
            c = c_even;
        } else {
            c = 1;
        }
        
        mpz_swap(approx.num.get_mpz_t(), approx.den.get_mpz_t());
        approx.num += approx.den * c;
    }
    std::cout << std::endl;
    return approx;
}

void continueFraction(Frac *frac, int_t c) {
    mpz_swap(frac->num.get_mpz_t(), frac->den.get_mpz_t());
    frac->num += frac->den * c;    
}

Frac approxE_ContinuedFractionTriplets(int_t n_3) {
    Frac e = {n_3 * 2, 1};
    for (int c_even = n_3 * 2 - 2; c_even > 0; c_even -= 2) {
        continueFraction(&e, 1);
        continueFraction(&e, 1);
        continueFraction(&e, c_even);
    }
    continueFraction(&e, 1);
    continueFraction(&e, 2);
    return e;
}

Frac approxPHI_ContinuedFraction(int_t n) {
    Frac phi = {1, 1};
    for (int i = 0; i < n; i++) {
        continueFraction(&phi, 1);
    }
    return phi;
}

#ifdef APPROX_CPP_MAIN
int main() {
    Frac num = approxPHI_ContinuedFraction(1000);

    std::cout << "Frac: " << num.num.get_str() << " / " << num.den.get_str() << "\n" << std::endl;

    std::cout << "Value: " << divideFraction(num, 10) << "\n" << std::endl;
    
    return 0;
}
#endif


#endif