# Generator for SAT factoring benchmarks

## Presentation

In a meeting with Armin Biere, Jaowei Chen, Yonathan Fisseha, Marijn
Heule, Karem Sakallah, had the idea of the factoring benchmark family:
We take prime numbers and check whether they can be factored into a
product of two numbers.

To make the family scale better, we had the idea to not take a fixed
interval, but instead to multiply the last prime number by a constant
factor (> 1). This turned out to produce benchmarks that scale well.


## Code

The code is implemented in C++. It actually produces an smt2 file and
we used bitwuzla to convert the SMT2 file to CNF. The naming
convention is the following: "factoring-<bitwidth>-<prime>.cnf".

All the problems are known UNSAT (modulo incorrect implementation of
the Sieve algorithm).

The code is slow and takes a few hours to run with the default options.

## Implementation

The code is simply a generator and is not expected to run multiple
times, so we actually implemented the sieve of Eratosthenes and did
not optimize it much.

The code use boost's program option library to parse options -- use
`sudo apt install libboost-all-dev` to install all boost libraries,
boost is useful for many projects anyway. 

To run the code, just run `make` in the terminal. Then to run it, use `./factoring-bench`. The options are:

  - `target-per-bitsize`: number of problems to generate per bitwidth
  
  - `bitwidth-start`: bitwidth of the first prime to generate
    numbers. Small numbers (< 33) will give trivial problems.

  - `bitwidth-end`: bitwidth of the last prime to generate
    numbers. Small numbers (< 33) will give trivial problems.
  
  - `dest-path`: directory to save the SMT2 files.