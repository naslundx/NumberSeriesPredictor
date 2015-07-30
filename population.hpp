#ifndef __POPULATION_HPP__
#define __POPULATION_HPP__

#include "genotype.hpp"
#include <vector>
#include <string>

class Population {
public:
  Population(double probability_flip, double probability_mutation);
  void reset(int size);
  Genotype get_best_fit();
  double get_total_fit();
  void next_generation();
  int current_generation();
  Genotype get_best_ever();
  void add_data_point(double x, double y);

private:
  Genotype select_copy_and_delete();

  std::vector<std::pair<double,double> > mInputData;
  std::vector<Genotype> mPopulation;
  int mSize;
  int mGenerationCount;
  double mProbFlip, mProbMutation;
  Genotype mBestEver;
};

#endif
