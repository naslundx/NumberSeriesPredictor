#include "numberseriespredictor.hpp"

int main(int argc, char* argv[]) {
  srand(time(NULL));
  const double match_tolerance = 999999.9;

  // Parse inputs
  if (argc < 4) {
    std::cout << "\nNot enough arguments. Specify population size (50), probability of flip (0.7) and probability of mutation (0.01).\n";
    return 0;
  }
  const int population_size = atoi(argv[1]);
  const double probability_flip = atof(argv[2]);
  const double probability_mutation = atof(argv[3]);

  // Keep track of the best
  Genotype best_ever_formula;

  // Setup the population (must be of even size)
  Population population(probability_flip, probability_mutation);
  population.add_data_point(1.0,4.0); // 3*x+1
  population.add_data_point(2.0,7.0);
  population.add_data_point(3.0,10.0);
  population.reset(population_size);

  // Loop until solution has been found
  while (true) {
    Genotype generation_best = population.get_best_fit();
    Genotype best_ever = population.get_best_ever();

    std::cout << "\n\nCurrent generation: " << population.current_generation();
    std::cout << "\nBest in this generation: " << generation_best << " (fitness=" << generation_best.fitness() <<")\n";
    std::cout << "\nBest ever: " << best_ever << " (fitness=" << best_ever.fitness() << ") [" << best_ever.formula(false) << "]\n";

    if (best_ever.fitness() > match_tolerance) {
      break;
    }

    population.next_generation();
  }

  return 0;
}
