#ifndef FACTOR
#define FACTOR

#include <cstdint>
#include <vector>

class PrimeFactor {
public:
  bool is_prime(uint64_t n) const;
private:
  mutable std::vector<uint64_t> primes = {2,3,5,7};
};
#endif