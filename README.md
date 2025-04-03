# Dirichlet's Theorem

## Continued Fraction Algorithm approximating PI

### Python
The Python version utilizes the arbitrarily large integer feature that already exists in python. Here is my prototypes for all the different methods for executing the algorithm, upon which I settled on the final ones I am using.

To run the file, navigate cmd to the python folder and type in:
`python main.py`

### C
The C version was my prototype for the c++ version. As such, it does not have arbitrarily large integers, instead using 64 bit integers as the maximum size.

To compile the file, navigate cmd to the c folder and type in:
`gcc -o main main.c`
And run the resulting file created to execute the program.

### C++
The C++ version is the final version used that is the most polished. It has a seperate library that performs arbitrarily large integer calculations.

To compile the file, navigate cmd to the c++ folder and type in:
`g++ -o main main.cpp`
And run the resulting file created to execute the program.
