#ifndef FRACTION_CPP
#define FRACTION_CPP

#include <iostream>
#include <cstdint>
#include <string>
#include "include/BigInt.hpp"

typedef int64_t int_t;

typedef struct {
    BigInt n;
    BigInt d;
} Fraction;

Fraction decimalToFraction(std::string num_string, int_t right_digits) {
    int_t left_digits = num_string.find(".");
    num_string.erase(left_digits, 1);
    num_string.erase(left_digits + right_digits);
    Fraction frac = {num_string, big_pow10(right_digits)};
    return frac;
}

Fraction wholeDecimalToFraction(std::string num_string) {
    int_t left_digits = num_string.find(".");
    num_string.erase(left_digits, 1);
    int_t right_digits = num_string.length() - left_digits;
    Fraction frac = {num_string, big_pow10(right_digits)};
    return frac;
}

Fraction simplifyFraction(Fraction frac) {
    BigInt _gcd = gcd(frac.n, frac.d);
    Fraction new_frac = {frac.n / _gcd, frac.d / _gcd};
    return new_frac;
}

std::string divideFraction(Fraction frac, int_t decimals) {
    int_t top_size = frac.n.to_string().length();
    int_t bottom_size = frac.d.to_string().length();

    int_t exponent = top_size - bottom_size;

    if (frac.d > frac.n) {
        exponent--;
    }

    BigInt division = frac.n * big_pow10(decimals - exponent) / frac.d;

    std::string num_string = division.to_string() + "e" + std::to_string(exponent);
    num_string.insert(1, 1, '.');
    return num_string;
}


Fraction absDifFraction(Fraction frac1, Fraction frac2) {
    BigInt n1 = frac1.n * frac2.d;
    BigInt n2 = frac2.n * frac1.d;
    BigInt n;
    if (n1 > n2) {
        n = n1 - n2;
    } else {
        n = n2 - n1;
    }
    BigInt d = frac1.d * frac2.d;
    
    Fraction dif_frac = {n, d};
    return dif_frac;
}

#endif