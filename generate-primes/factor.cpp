#include "factor.hpp"
#include <math.h>

bool PrimeFactor::is_prime(uint64_t n) const {
  const uint64_t sq = std::sqrt(n)+1;
  bool is_prime = true;
  bool finished = false;

  for (const auto prime: primes) {
    if (prime > sq)
      {finished = true; break;}
    if (! (n % prime))
      {is_prime = false; finished = true; break;}
  }

  if (finished)
    return is_prime;

  uint64_t num = primes.back();
  num += 2;
  while (num <= sq) {
    bool num_prime = true;
    for (const auto prime: primes) {
      if (! (num % prime)){
	num_prime = false; break;}
    }

    if (!num_prime)
      {num += 2; continue;}
    primes.push_back(num);
    if (! (n % num)) {
      is_prime = false;
      return false;
    }
    num += 2;
  }

  return true;
}