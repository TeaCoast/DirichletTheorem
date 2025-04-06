#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "gmp/mini-gmp.c"
#include "gmp/mini-mpq.c"

#include "pi.h"

typedef int64_t int_t;

/* Goals:
1. create a arbitrary precision rational number
2. perform required operations on rational number
3. pass the rational number to a function
4. create a list of rational numbers
*/

typedef struct {
    mpq_t lo;
    mpq_t hi;
} ARange;

ARange decToARange(char* number_string, int_t right_digits) {
    int_t number_size = strlen(number_string);

    // create numerator and denominator string
    char* num_string = malloc(number_size);
    char* den_string = malloc(number_size);
    den_string[0] = '1';
    
    int_t num_size = 0;
    int_t den_size = 1;

    // copy number string into numerator and denominator strings
    for (int_t i = 0; i < number_size; i++) {
        if (number_string[i] == '.') {
            break;
        }
        num_string[num_size] = number_string[i];
        num_size++;
    }
    for (int_t i = 0; i < right_digits; i++) {
        num_string[num_size] = number_string[num_size + 1];
        num_size++;
        den_string[den_size] = '0';
        den_size++;
    }

    // convert numerator and denominator string into mpz integers
    mpz_t num1, num2, den;

    mpz_init(num1);
    mpz_init(num2);
    mpz_init(den);
    
    mpz_set_str(num1, num_string, 10);
    mpz_add_ui(num2, num1, 1);
    mpz_set_str(den, den_string, 10);

    free(num_string);
    free(den_string);

    // convert mpz integers into mpq rational numbers
    ARange arange;

    mpq_init(arange.lo);
    mpq_init(arange.hi);

    mpq_set_num(arange.lo, num1);
    mpq_set_num(arange.hi, num2);
    mpq_set_den(arange.lo, den);
    mpq_set_den(arange.hi, den);
    
    mpz_clear(num1);
    mpz_clear(num2);
    mpz_clear(den);

    return arange;
}

int cfaSimple(mpq_t a, int_t n, mpz_t* c_list) {
    mpz_t c;
    mpq_t c_sub, r;
    mpz_init(c);
    mpq_init(c_sub);
    mpq_init(r);

    mpq_set(r, a);
    
    for (int_t i = 0; i < n; i++) {
        mpz_fdiv_q(c, mpq_numref(r), mpq_denref(r));

        mpz_init(c_list[i]);
        mpz_set(c_list[i], c);
        
        mpq_set_num(c_sub, c);
        mpq_sub(r, r, c_sub);
        
        if (mpz_cmp_si(mpq_numref(r), 0) == 0) {
            mpz_clear(c);
            mpq_clear(c_sub);
            mpq_clear(r);
            return i;
        }   
        mpq_inv(r, r);
    }
    mpz_clear(c);
    mpq_clear(c_sub);
    mpq_clear(r);
    return n;    
}

int cfaLimit(ARange arange, int_t n, mpz_t* c_list) {
    mpz_t c1, c2;
    mpq_t c_sub, r1, r2;
    mpz_init(c1);
    mpz_init(c2);
    mpq_init(c_sub);
    mpq_init(r1);
    mpq_init(r2);
    
    mpq_set(r1, arange.lo);
    mpq_set(r2, arange.hi);
    
    for (int_t i = 0; i < n; i++) {
        mpz_fdiv_q(c1, mpq_numref(r1), mpq_denref(r1));
        mpz_fdiv_q(c2, mpq_numref(r2), mpq_denref(r2));    
        if (mpz_cmp(c1, c2) != 0) {
            mpz_clear(c1);
            mpz_clear(c2);
            mpq_clear(c_sub);
            mpq_clear(r1);
            mpq_clear(r2);
            return i;
        }
        
        mpz_init(c_list[i]);
        mpz_set(c_list[i], c1);
        
        mpq_set_num(c_sub, c1);
        mpq_sub(r1, r1, c_sub);
        mpq_sub(r2, r2, c_sub);

        if (mpz_cmp_si(mpq_numref(r1), 0) == 0 || mpz_cmp_si(mpq_numref(r2), 0) == 0) {
            mpz_clear(c1);
            mpz_clear(c2);
            mpq_clear(c_sub);
            mpq_clear(r1);
            mpq_clear(r2);
            return i;
        }
        
        mpq_inv(r1, r1);
        mpq_inv(r2, r2);    
    }
    mpz_clear(c1);
    mpz_clear(c2);
    mpq_clear(c_sub);
    mpq_clear(r1);
    mpq_clear(r2);
    return n;    
}


int main() {
    char* number_string = PI;
    
    ARange arange = decToARange(number_string, 10);
    
    printf("Result: ");
    mpq_out_str(stdout, 10, arange.lo);
    printf("\n");

    int_t n = 10;
    mpz_t c_list[n];

    int_t length = cfaLimit(arange, n, c_list);

    for (int_t i = 0; i < length; i++) {
        mpz_out_str(stdout, 10, c_list[i]);
        printf(", ");
        mpz_clear(c_list[i]);
    }
    printf("\n");
    
    mpq_clear(arange.lo);
    mpq_clear(arange.hi);
    
    return 0;
}