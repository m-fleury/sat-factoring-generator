#include "generate_problem.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string binary_number(uint64_t x, uint64_t digits) {
  std::string num;
  for (int i = digits-1; i >= 0; --i) {
    num += (x & ((uint64_t)1 << i) ? '1' : '0');
  }
  return num;
}

std::ostream &operator<<(std::ostream &stream, const Generate_Problem &p) {

  std::ostringstream bitvec_type;
  bitvec_type << "(_ BitVec " << p.base << ")";

  std::ostringstream one;
  one << binary_number(1, p.base);

  std::ostringstream f;
  f << binary_number(p.factored, p.base);

  stream << "(set-info :smt-lib-version 2.6)\n"
  << "(set-logic QF_BV)\n"
  << "(set-option :produce-models true)\n"
  << "(set-info :status sat)\n"
  << "\n"
  << "(declare-fun a () " << bitvec_type.str() << ")\n"
  << "(declare-fun c () " << bitvec_type.str() << ")\n"
  << "(declare-fun d () " << bitvec_type.str() << ")\n"
  << "\n"
  << "(assert (= a (bvmul c d)))\n"
  << "(assert (= a #b" << f.str() << "))\n"
  << "\n"
  << "; prime factorization: avoid 1\n"
  << "(assert (not (= c #b" << one.str() << ")))\n"
  << "(assert (not (= d #b" << one.str() << ")))\n"
  << "\n"
  << "; ensure that there is no overflow\n"
  << "(assert (not (bvumulo c d)))\n"
  << "; ensure that there is no overflow\n"
  << "(assert (bvult c d))\n"
  << "(check-sat)\n"
  << "(exit)\n";

  return stream;
}