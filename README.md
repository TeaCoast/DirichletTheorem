# Dirichlet's Theorem

## Continued Fraction Algorithm approximating PI

### C++ with BigInt
C++ version uses the BigInt arbitrary precision integer library.

To compile the file, navigate cmd to the c++BigInt folder and type in:
`g++ -o main main.cpp`
And run the resulting file created to execute the program.

### C with GMP
This C version uses the GMP arbitrary precision library, which is a lot more verbose because of being a c library.

To compile the file, navigate cmd to the c-gmp folder and type in:
`gcc -o main main.c`
And run the resulting file created to execute the program.

### C
C version has a max integer size of 64 bits.

To compile the file, navigate cmd to the c folder and type in:
`gcc -o main main.c`
And run the resulting file created to execute the program.

### Python
The Python version utilizes the arbitrarily large integer feature that already exists in python. Here is my prototypes for all the different methods for executing the algorithm, upon which I settled on the final ones I am using.

To run the file, navigate cmd to the python folder and type in:
`python main.py`


