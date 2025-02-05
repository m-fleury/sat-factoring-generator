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
relies on bitwuzla to convert the file to CNF. The naming convention
is the following: "factoring-<bitwidth>-<prime>.cnf".

All the problems are known UNSAT (modulo incorrect implementation of
the Sieve algorithm).

The code is slow and takes a few hours to run with the default options.

## Implementation

The code is simply a generator and is not expected to run multiple
times, so we actually implemented the sieve of Eratosthenes and did
not optimize it much.