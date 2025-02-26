#include "generate_problem.hpp"
#include "factor.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



uint64_t previous_prime(PrimeFactor &factor, uint64_t n) {
  if (!(n % 2))
    n -= 1;
  if (n)
    while (!factor.is_prime(n)) {
      n -= 2;
    }

  return n;
}

uint64_t next_prime(PrimeFactor &factor, uint64_t n) {
  if (!(n % 2))
    n += 1;
  while (!factor.is_prime(n)) {
    n += 2;
  }

  return n;
}



int main() {
  std::cout << Generate_Problem(63, 4294967297);


  PrimeFactor factor;

  // TODO number of intervals to produce prime numbers
  const uint64_t target_per_bitsize = 50-1;

  // TODO constants to change for the various experiments
  const int bitwidth_start = 33;
  const int bitwidth_end = 48;

  for (int bitwidth = bitwidth_start - 1; bitwidth < bitwidth_end - 1; ++bitwidth) {
    std::cout << "starting with bitwidth " << bitwidth << "\n";
    const uint64_t start = ((uint64_t)1 << bitwidth) + (uint64_t)1;
    const uint64_t last = ((uint64_t)1 << (bitwidth + 1)) - (uint64_t)1;

    uint64_t num = start;
    
    for (uint64_t k = 0; k <= target_per_bitsize; ++k) {
      num = start + static_cast<uint64_t>(((float)k * ((uint64_t)1<<bitwidth)) / (float)(target_per_bitsize+1));
      //std::cout << "start = " << num << "; k=" << k << "&" << (uint64_t)(((uint64_t)1<<bitwidth)) << "\n";
      num = next_prime(factor, num);
      if (num > last)
      	continue;
      std::cout << num << "\n";
      std::ofstream myfile;
      std::ostringstream file_name;
      file_name << "/tmp/factoring-smtlib/factoring-" << bitwidth+1 << "-" << num << ".smt2";

      myfile.open (file_name.str());
      myfile << Generate_Problem(bitwidth+1, num);
      myfile.close();

      std::ostringstream file_name_cnf;
      file_name_cnf << "/tmp/factoring-cnf/factoring-" << bitwidth+1 << "-" << num << ".cnf";

      const std::string bitwuzla = "/home/fleury/bin/bitwuzla --dump-dimacs " + file_name.str() + " > " + file_name_cnf.str();
      std::system(bitwuzla.c_str());
    }
  }
}
