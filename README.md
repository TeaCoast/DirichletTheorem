# Dirichlet's Theorem

## Continued Fraction Algorithm approximating PI

### c++-mini-gmp
The C++ mini-gmp version uses a mini-gmp c++ wrapper for the c mini-gmp files, but this does not include rational numbers, so those must be added manually. This folder also includes additional constants that the CFA algorithm can approximate.

To compile this file, navigate cmd to the c++mini-gmp folder and type in:
`g++ -o main main.cpp`
And run the resulting file created to execute the library

### c++-gmp
C++ GMP version uses the full version of the GMP library, meaning it includes integers, rationals, and floats, but it must be built separately, and the following build library must be added to the lib folder. This version also uses the official c++ wrapper for the library.

To compile the file, navigate cmd to the c++gmp folder and type in:
`g++ -I ./include -L ./lib -o main main.cpp -lgmp
And run the resulting file created to execute the program.`

### c++BigInt
C++ BigInt version uses the BigInt arbitrary precision integer library.

To compile the file, navigate cmd to the c++BigInt folder and type in:
`g++ -o main main.cpp`
And run the resulting file created to execute the program.

### c-mini-gmp
This C version uses the mini version of the GMP arbitrary precision library, which is a lot more verbose because of being a c library. It includes both integers and rationals.

To compile the file, navigate cmd to the c-mini-gmp folder and type in:
`gcc -o main main.c`
And run the resulting file created to execute the program.

### c
C version has a max integer size of 64 bits.

To compile the file, navigate cmd to the c folder and type in:
`gcc -o main main.c`
And run the resulting file created to execute the program.

### python
The Python version utilizes the arbitrarily large integer feature that already exists in python.

To run the file, navigate cmd to the python folder and type in:
`python main.py`


