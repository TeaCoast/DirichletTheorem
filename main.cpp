#include <iostream>
#include <cstdint>
#include <string>
#include "include/BigInt.hpp"
#include "pi.hpp"


typedef int64_t int_t;


Fraction simplify_c_list_to_fraction(int_t n, BigInt* c_list) {
    if (n == 1) {
        Fraction frac = {c_list[0], 1};
        return frac;
    }
    Fraction frac = {1, c_list[n - 1]};
    int_t i = n - 2;
    while (i > 0) {
        BigInt n_old = frac.n;
        frac.n = frac.d;
        frac.d = c_list[i] * frac.d + n_old;
        i--;
    }
    frac.n = c_list[0] * frac.d + frac.n;
    return frac;
}

int simple_cfa(Fraction a_frac, int_t n, BigInt* c_list) {
    BigInt c = a_frac.n / a_frac.d;

    Fraction r_frac = {a_frac.d, a_frac.n - c * a_frac.d};

    c_list[0] = c;

    for (int_t i = 1; i < n; i++) {
        if (r_frac.d == 0) {
            return i;
        }

        c = r_frac.n / r_frac.d;

        c_list[i] = c;

        BigInt old_rn = r_frac.n;

        r_frac.n = r_frac.d;
        r_frac.d = old_rn - c * r_frac.d;
    }
    return n;    
}

int cfa_limit(Fraction a1_frac, Fraction a0_frac, int_t n, BigInt* c_list) {
    BigInt c0 = a0_frac.n / a0_frac.d;
    BigInt c1 = a1_frac.n / a1_frac.d;
    if (c0 != c1) {
        return 0;
    }
    BigInt c = c0;

    Fraction r0_frac = {a0_frac.d, a0_frac.n - c * a0_frac.d};
    Fraction r1_frac = {a1_frac.d, a1_frac.n - c * a1_frac.d};

    c_list[0] = c;

    for (int_t i = 1; i < n; i++) {
        if (r0_frac.d == 0 || r1_frac.d == 0) {
            return i;
        }

        BigInt c0 = r0_frac.n / r0_frac.d;
        BigInt c1 = r1_frac.n / r1_frac.d;
        if (c0 != c1) {
            return i;
        }
        BigInt c = c0;

        c_list[i] = c;

        BigInt old_r0n = r0_frac.n;
        r0_frac.n = r0_frac.d;
        r0_frac.d = old_r0n - c * r0_frac.d;
        
        BigInt old_r1n = r1_frac.n;
        r1_frac.n = r1_frac.d;
        r1_frac.d = old_r1n - c * r1_frac.d;
    }
    return n;    
}


int main() {
    // get lower and upper ranges for alpha
    Fraction pi_frac = decimalToFraction(PI, 1000);
    Fraction pi_frac_upper = {pi_frac.n + 1, pi_frac.d};

    // get c list
    int_t n = 1000;
    BigInt c_list[n];
    int_t length = cfa_limit(pi_frac, pi_frac_upper, n, c_list);

    // print c list
    std::cout << "c list (" << length << " elements) = \n" << c_list[0];
    for (int_t i = 1; i < length; i++) {
        std::cout << ", " << c_list[i];
    }
    std::cout << std::endl;

    // print alpha approximation as fraction
    Fraction approx = simplify_c_list_to_fraction(length, c_list);
    std::cout << "alpha approximation = \n" << approx.n << " / " << approx.d << "\n" << std::endl;

    // check and display accuracy of approximation
    Fraction full_pi_frac = wholeDecimalToFraction(PI);
    Fraction dif_frac = absDifFraction(approx, full_pi_frac);
    
    std::string dif_string = divideFraction(dif_frac, 4);
    std::cout << "a - p/q = " << dif_string << std::endl;
    
    return 0;
}