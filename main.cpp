#include "generate_problem.hpp"
#include "factor.hpp"
#include "boost/program_options.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <ostream>
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
// the default log2 works only on double and is just not good enough here.
uint64_t log2 (uint64_t n) {
  uint64_t index = n;
  uint64_t target_level = 0;
  while (index >>= 1) ++target_level;
  return target_level;
}

int main(int argc, char *argv[]) {
  std::cout << Generate_Problem(63, 4294967297);

  PrimeFactor factor;

  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("target-per-bitsize", po::value<uint64_t>()->default_value(50 - 1), "Number of prime numbers per interval")
    ("bitwidth-start", po::value<int>()->default_value(33), "Starting bitwidth")
    ("bitwidth-end", po::value<int>()->default_value(48), "Last bitwidth")
    ("dest-path", po::value<std::string>()->default_value("/tmp/factoring-smtlib"), "Destination directory");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  const uint64_t target_per_bitsize = vm["target-per-bitsize"].as<uint64_t>();
  const int bitwidth_start = vm["bitwidth-start"].as<int>();
  const int bitwidth_end = vm["bitwidth-end"].as<int>();
  const std::string path = vm["dest-path"].as<std::string>();

  for (int bitwidth = bitwidth_start - 1; bitwidth < bitwidth_end - 1; ++bitwidth) {
    std::cout << "starting with bitwidth " << bitwidth << "\n";
    const uint64_t start = ((uint64_t)1 << bitwidth) + (uint64_t)1;
    uint64_t last = ((uint64_t)1 << (bitwidth + 1)) - (uint64_t)1;

    uint64_t num = start;

    uint64_t first_prime, second_prime;
    for (uint64_t k = 0; k <= target_per_bitsize; ++k) {
      num =
          start + static_cast<uint64_t>(((float)k * ((uint64_t)1 << bitwidth)) /
                                        (float)(target_per_bitsize + 1));
      last = start + static_cast<uint64_t>(
                         ((float)(k + 1) * ((uint64_t)1 << bitwidth)) /
                         (float)(target_per_bitsize + 1));
      first_prime = next_prime(factor, num);
      for (; first_prime < last;) {
        second_prime = next_prime(factor, 2+first_prime);
        const uint64_t num = first_prime * second_prime;
	const uint64_t base = log2 (num) + 1;
	const uint64_t distance = second_prime - first_prime;
        if (distance <= 10 && base < 64) {
          //          std::cout << num << "\n";
          std::ofstream myfile;
          std::ostringstream file_name;
          file_name << path << "/factoring-" << bitwidth + 1 << "-" << distance
                    << "-" << first_prime << "x" << second_prime << ".smtlib";

          myfile.open(file_name.str());
	  if (myfile.fail()) {
	    std::cerr << "could not open file " << file_name.str() << "\n";
	    abort();
	  }
          myfile << Generate_Problem(base, num);
          myfile.close();

          std::ostringstream file_name_cnf;
          file_name_cnf << path << "/factoring-" << bitwidth + 1 << distance
                        << "-" << first_prime << "x" << second_prime << ".cnf";
          // std::cout << file_name_cnf.str() << "\n";

          // const std::string bitwuzla =
          //     "/home/fleury/bin/bitwuzla --dump-dimacs " + file_name.str() +
          //     " > " + file_name_cnf.str();
          // std::system(bitwuzla.c_str());
          break;
        } else {
          first_prime = second_prime;
        }
      }
    }
  }
}
