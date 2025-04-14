#ifndef FRAC_CPP
#define FRAC_CPP

#include <iostream>
#include <cstdint>
#include <string>
#include "gmp/mini-gmp.c"
#include "gmp/mini-gmp.h"
#include "gmp/mini-gmpxx.h"

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


Frac cListToFrac(int_t n, int_t* c_list) {
    Frac approx = {c_list[n - 1], 1};
    for (int_t i = n - 2; i >= 0; i--) {
        mpz_swap(approx.num.get_mpz_t(), approx.den.get_mpz_t());
        approx.num += approx.den * c_list[i];
    }
    return approx;
}


int_t cListToFracList(int_t n_c, int_t* c_list, int_t n_frac, Frac* frac_list) {
    if (n_c < n_frac) 
        n_frac = n_c;
    frac_list[0] = {c_list[0], 1};
    if (n_frac == 1)
        return n_frac;
    frac_list[1] = {frac_list[0].num * c_list[1] + 1, c_list[1]};
    for (int_t i = 2; i < n_frac; i++) {
        frac_list[i].num = c_list[i] * frac_list[i - 1].num + frac_list[i - 2].num;
        frac_list[i].den = c_list[i] * frac_list[i - 1].den + frac_list[i - 2].den;
    }
    return n_frac;
}

#endif