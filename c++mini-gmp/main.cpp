#include <iostream>
#include <cstdint>
#include <string>
#include "gmp/mini-gmp.c"
#include "gmp/mini-gmp.h"
#include "gmp/mini-gmpxx.h"

#include "pi.hpp"

typedef int64_t int_t;

typedef struct {
    mpz_class num;
    mpz_class den;
} Frac;

typedef struct {
    Frac lo;
    Frac hi;
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

    Frac lo = {num, den};
    Frac hi = {num+1, den};

    RationalRange rRange= {lo, hi};
    return rRange;
}


Frac cListToFrac(int_t n, int_t* c_list) {
    Frac approx = {c_list[n - 1], 1};
    for (int_t i = n - 2; i >= 0; i--) {
        mpz_swap(approx.num.get_mpz_t(), approx.den.get_mpz_t());
        approx.num += approx.den * c_list[i];
    }
    return approx;
}

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

std::string divideFraction(Frac frac, int_t decimals) {
    Frac absFrac;
    mpz_abs(absFrac.num.get_mpz_t(), frac.num.get_mpz_t());
    mpz_abs(absFrac.den.get_mpz_t(), frac.den.get_mpz_t());

    //std::cout << "frac: " << frac.num.get_str() << " / " << frac.den.get_str() << "\n" << std::endl;
    //std::cout << "abs frac: " << absFrac.num.get_str() << " / " << absFrac.den.get_str() << "\n" << std::endl;
    
    std::string num_string = absFrac.num.get_str();
    std::string den_string = absFrac.den.get_str();
    
    int_t exponent = num_string.length() - den_string.length();

    int_t den_1 = den_string[0] - '0';
    int_t num_1 = num_string[0] - '0';
    
    if (den_1 > num_1) {
        exponent--;
    }

    mpz_class multiplier;
    mpz_ui_pow_ui(multiplier.get_mpz_t(), 10, decimals - exponent);
    mpz_class division = frac.num * multiplier / frac.den;
    std::string div_string = division.get_str() + "e" + std::to_string(exponent);
    if (div_string[0] == '-') {
        div_string.insert(1, 1, '.');
    } else {
        div_string.insert(1, 1, '.');
    }
    return div_string;
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
    
    return 0;
}