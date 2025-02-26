#ifndef GENERATE_PROBLEM
#define GENERATE_PROBLEM

#include <cassert>
#include <stdint.h>
#include <string>

class Generate_Problem {
public:
  Generate_Problem(uint64_t b, uint64_t a) : base(b), factored(a) {
    assert(factored < ((uint64_t)1 << base));
  }

  friend std::ostream &operator<<(std::ostream &stream,
                                  const Generate_Problem &p);

private:
  uint64_t base;
  uint64_t factored;
};

#endif