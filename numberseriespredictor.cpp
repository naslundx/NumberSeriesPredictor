#include "numberseriespredictor.hpp"

int main() {
  srand(time(NULL));
  int generations = 0;
  Genotype best_ever_formula;
  double best_ever_fit = 0.0;

  // Input data (x^2 + 1)
  std::vector<std::pair<double,double> > input_data;
  input_data.push_back(std::pair<double,double>(1.0,2.0));
  input_data.push_back(std::pair<double,double>(2.0,4.0));
  input_data.push_back(std::pair<double,double>(3.0,6.0));

  // Setup the population (must be of even size)
  const int population_size = 200;
  Population population(population_size, input_data);

  // Loop until solution has been found
  while (generations < 10000) {
    std::cout << "\n\nCurrent generation: " << generations;

    Genotype best = population.get_best_fit();
    double best_fitness = best.fitness(input_data);
    if (best_fitness > best_ever_fit) {
      best_ever_fit = best_fitness;
      best_ever_formula = best;
    }
    std::cout << "\nBest in this generation: " << best << " (fitness=" << best_fitness<<")\n";
    std::cout << "\nBest ever: " << best_ever_formula << " (fitness=" << best_ever_fit << ")\n";
    if (best_fitness > match_tolerance) {
      break;
    }

    generations++;
    population.next_generation();
  }
}
