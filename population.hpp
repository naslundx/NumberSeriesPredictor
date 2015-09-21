#ifndef __POPULATION_HPP__
#define __POPULATION_HPP__

#include "genotype.hpp"
#include <vector>
#include <string>

class Population {
public:
  Population(int size, std::vector<std::pair<double,double> >& input_data);
  Genotype get_best_fit();
  double get_total_fit();
  void next_generation();

private:
  Genotype select_copy_and_delete();

  std::vector<std::pair<double,double> > mInputData;
  std::vector<Genotype> mPopulation;
  int mSize;
};

#endif
