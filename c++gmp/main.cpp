#include <iostream>
#include <cstdint>
#include <string>
#include "gmp.h"
#include "gmpxx.h"
#include "pi.hpp"

typedef int64_t int_t;

typedef struct {
    mpq_class lo;
    mpq_class hi;
} RationalRange;

RationalRange decToRRange(std::string dec_str, int_t right_digits) {
    int_t left_digits = dec_str.find(".");
    dec_str.erase(left_digits, 1);
    if (right_digits != -1) {
        dec_str.erase(left_digits + right_digits);
    } else {
        right_digits = dec_str.length() - left_digits;
    }
    
    mpz_class num(dec_str);
    mpz_class den;
    mpz_ui_pow_ui(den.get_mpz_t(), 10, right_digits);

    mpq_class lo(num, den);
    mpq_class hi(num+1, den);

    RationalRange rRange= {lo, hi};
    return rRange;
}

mpq_class cListToFrac(int_t n, int_t* c_list) {
    mpq_class approx(c_list[n - 1], 1);
    for (int_t i = n - 2; i >= 0; i--) {
        approx = 1 / approx;
        approx += c_list[i];
    }
    return approx;
}

int_t cfaSimple(mpq_class a, int_t n, int_t* c_list) {
    mpz_class c;
    mpq_class r;
    r = a;
    for (int_t i = 0; i < n; i++) {
        c = r / 1;
        c_list[i] = c.get_ui();;
        r -= c;
        if (mpq_sgn(r.get_mpq_t()) == 0) {
            return i + 1;
        }
        r = 1 / r;
    }
    return n;
}

int_t cfaStop(RationalRange aRange, int_t n, int_t* c_list) {
    mpz_class c1, c2;
    mpq_class r1, r2;
    r1 = aRange.lo;
    r2 = aRange.hi;
    for (int_t i = 0; i < n; i++) {
        c1 = r1 / 1;
        c2 = r2 / 1;
        if (c1 != c2) {
            return i;
        }
        c_list[i] = c1.get_ui();
        r1 -= c1;
        r2 -= c2;
        if (mpq_sgn(r1.get_mpq_t()) == 0 || mpq_sgn(r2.get_mpq_t()) == 0) {
            return i + 1;
        }
        r1 = 1 / r1;
        r2 = 1 / r2;
    }
    return n;
}

int main() {
    std::string alpha_str = PI;
    
    RationalRange alphaRange = decToRRange(alpha_str, -1);

    //std::cout << "low: " << alphaRange.lo.get_str() << ", high: " << alphaRange.hi.get_str() << std::endl;    
    std::cout << "Alpha Approximation: " << alphaRange.lo.get_str() << "\n" << std::endl;
    
    int_t n = 1000;
    int_t c_list[n];
    n = cfaStop(alphaRange, n, c_list);
    
    std::cout << "c list (count " << std::to_string(n) << "): \n";
    std::cout << std::to_string(c_list[0]);
    for (int_t i = 1; i < n; i++) {
        std::cout << ", " << std::to_string(c_list[i]);
    }
    std::cout << "\n" << std::endl;

    mpq_class approx = cListToFrac(n, c_list);

    std::cout << "p / q = " << std::endl;
    std::cout << approx.get_str() << std::endl;

    mpf_class diff(approx - alphaRange.lo);

    gmp_printf("a - p / q: %.5Fe\n", diff);
    
    return 0;
}