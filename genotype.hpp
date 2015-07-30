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

class Genotype {
public:
  Genotype();
  Genotype(std::vector<std::pair<double,double> > series);
  void randomize_content(const int length);
  double fitness();
  char& operator[](int i);
  Genotype& operator%(Genotype& rhs);
  void mutate();
  void setProbabilities(double probability_flip, double probability_mutation);
  std::string formula(bool only_valid);
  friend std::ostream& operator<<(std::ostream& os, Genotype& dt);

private:
  double value_error(double& x, double& y);
  double penalty();

  double mProbFlip, mProbMutation, mFitness;

  std::vector<char> mData;
  std::vector<std::pair<double,double> > mInputData;

  char cexpr(int pos);
  int expr(int pos);
};

#endif
