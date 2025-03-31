#include <stdio.h>
#include <stdint.h>

typedef int64_t int_t;

typedef struct {
    int_t n;
    int_t d;
} Fraction;

int simple_cfa(Fraction a_frac, int_t n, int_t* c_list) {
    int_t c = a_frac.n / a_frac.d;

    Fraction r_frac = {a_frac.d, a_frac.n - c * a_frac.d};

    c_list[0] = c;

    for (int_t i = 1; i < n; i++) {
        if (r_frac.d == 0) {
            return i;
        }

        c = r_frac.n / r_frac.d;

        c_list[i] = c;

        int_t old_rn = r_frac.n;

        r_frac.n = r_frac.d;
        r_frac.d = old_rn - c * r_frac.d;
    }
    return n;    
}

int cfa_limit(Fraction a1_frac, Fraction a0_frac, int_t n, int_t* c_list) {
    int_t c0 = a0_frac.n / a0_frac.d;
    int_t c1 = a1_frac.n / a1_frac.d;
    if (c0 != c1) {
        return 0;
    }
    int_t c = c0;

    Fraction r0_frac = {a0_frac.d, a0_frac.n - c * a0_frac.d};
    Fraction r1_frac = {a1_frac.d, a1_frac.n - c * a1_frac.d};

    c_list[0] = c;

    for (int_t i = 1; i < n; i++) {
        if (r0_frac.d == 0 || r1_frac.d == 0) {
            return i;
        }

        int_t c0 = r0_frac.n / r0_frac.d;
        int_t c1 = r1_frac.n / r1_frac.d;
        if (c0 != c1) {
            return i;
        }
        int_t c = c0;

        c_list[i] = c;

        int_t old_r0n = r0_frac.n;
        r0_frac.n = r0_frac.d;
        r0_frac.d = old_r0n - c * r0_frac.d;
        
        int_t old_r1n = r1_frac.n;
        r1_frac.n = r1_frac.d;
        r1_frac.d = old_r1n - c * r1_frac.d;
    }
    return n;    
}

int main() {

    //char* PI = "3.14159265358979323846264";

    Fraction pi_frac = {3141592653, 1000000000};
    Fraction pi_frac_upper = {pi_frac.n + 1, pi_frac.d};

    int_t n = 7;
    int_t c_list[n];

    int_t length = cfa_limit(pi_frac, pi_frac_upper, n, c_list);

    for (int_t i = 0; i < length; i++) {
        printf("%i, ", c_list[i]);
    }
    printf("\n");

    return 0;
}