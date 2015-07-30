#ifndef __GENOTYPE_HPP_
#define __GENOTYPE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <random>
#include <limits>
#include <iostream>
#include <time.h>

#define probability_mutation 0.1
#define probability_flip 0.65
#define match_tolerance 99.9

class Genotype {
public:
  Genotype();
  void randomize_content(const int length);
  double fitness(std::vector<std::pair<double,double> >& series);
  char& operator[](int i);
  Genotype& operator%(Genotype& rhs);
  void mutate();
  std::string formula(bool only_valid);
  friend std::ostream& operator<<(std::ostream& os, Genotype& dt);

private:
  double value_error(double& x, double& y);
  double penalty();

  std::vector<char> mData;

  char cexpr(int pos);
  int expr(int pos);
};

#endif
