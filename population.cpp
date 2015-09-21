#include "population.hpp"

Population::Population(int size, std::vector<std::pair<double,double> >& input_data) {
  mSize = size;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  mGenerationCount = 0;

  const int genotype_length = 3*15;
=======
  mInputData = input_data;
  const int genotype_length = 4*15;
>>>>>>> parent of 2de0501... Improved performance, uses CLI arguments
=======
  mInputData = input_data;
  const int genotype_length = 4*15;
>>>>>>> parent of 2de0501... Improved performance, uses CLI arguments
=======
  mInputData = input_data;
  const int genotype_length = 4*15;
>>>>>>> parent of 2de0501... Improved performance, uses CLI arguments

  for (int i=0; i<mSize; i++) {
    Genotype temp;
    temp.randomize_content(genotype_length);
    mPopulation.push_back(temp);
  }
}

Genotype Population::get_best_fit() {
  double max = 0;
  std::vector<Genotype>::iterator best;

  for (auto it = mPopulation.begin(); it != mPopulation.end(); ++it) {
    if (it->fitness(mInputData) > max) {
      best = it;
    }
  }

  return *best;
}

double Population::get_total_fit() {
  double sum = 0.0;
  for (auto it = mPopulation.begin(); it != mPopulation.end(); ++it) {
    sum += it->fitness(mInputData);
  }
  return sum;
}

Genotype Population::select_copy_and_delete() {
  double total = this->get_total_fit();
  double frac = total * ((double)rand() / std::numeric_limits<double>::max());
  double counter = 0.0;

  for (auto it = mPopulation.begin(); it != mPopulation.end(); ++it) {
    counter += it->fitness(mInputData);
    if (counter > frac) {
      Genotype temp = *it;
      mPopulation.erase(it);
      return temp;
    }
  }

  Genotype temp = mPopulation.back();
  mPopulation.erase(mPopulation.end()-1);
  return temp;
}

void Population::next_generation() {
  std::vector<Genotype> new_population;

  for (int x=mPopulation.size()-1; x>=0; x-=2) {
    Genotype a = select_copy_and_delete();
    Genotype b = select_copy_and_delete();

    // Cross over and mutate, then add to the pool
    a % b;
    new_population.push_back(a);
    new_population.push_back(b);
  }

  // Add the new individuals to the population
  for (auto it=new_population.begin(); it!=new_population.end(); ++it) {
    Genotype temp = *it;
    mPopulation.push_back(temp);
  }
}
