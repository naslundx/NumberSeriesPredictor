#include "population.hpp"

Population::Population(double probability_flip, double probability_mutation) {
  mGenerationCount = 0;
  mProbFlip = probability_flip;
  mProbMutation = probability_mutation;
}

void Population::reset(int size) {
  mSize = size;
  mGenerationCount = 0;

  const int genotype_length = 4*15;

  mPopulation.clear();

  for (int i=0; i<mSize; i++) {
    Genotype temp(mInputData);
    temp.randomize_content(genotype_length);
    temp.setProbabilities(mProbFlip, mProbMutation);
    mPopulation.push_back(temp);
  }
}

void Population::add_data_point(double x, double y) {
  mInputData.push_back(std::pair<double,double>(x,y));
}

Genotype Population::get_best_fit() {
  double max = 0;
  std::vector<Genotype>::iterator best;

  for (auto it = mPopulation.begin(); it != mPopulation.end(); ++it) {
    if (it->fitness() > max) {
      best = it;
    }
  }

  return *best;
}

double Population::get_total_fit() {
  double sum = 0.0;
  for (auto it = mPopulation.begin(); it != mPopulation.end(); ++it) {
    sum += it->fitness();
  }
  return sum;
}

Genotype Population::select_copy_and_delete() {
  double total = this->get_total_fit();
  double frac = total * ((double)rand() / std::numeric_limits<double>::max());
  double counter = 0.0;

  for (auto it = mPopulation.begin(); it != mPopulation.end(); ++it) {
    counter += it->fitness();
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
  mGenerationCount++;
  std::vector<Genotype> new_population;

  // Advance in time
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

int Population::current_generation() {
  return mGenerationCount;
}

Genotype Population::get_best_ever() {
  // Check if any one of them are the best ever
  Genotype best = get_best_fit();
  if (mGenerationCount == 0) {
    mBestEver = best;
  }
  else {
    if (best.fitness() > mBestEver.fitness()) {
      mBestEver = best;
    }
  }

  // Hack to add the two best ever individuals back
  if (mGenerationCount > 10) {
    //mPopulation.pop_back();
    //mPopulation.pop_back();
    //mPopulation.push_back(mBestEver);
    //mPopulation.push_back(mBestEver);
  }

  return mBestEver;
}
