#include <ortools/algorithms/knapsack_solver.h>

#include <rice/rice.hpp>

using operations_research::KnapsackSolver;

using Rice::Array;
using Rice::Object;
using Rice::Symbol;

template<>
inline
KnapsackSolver::SolverType from_ruby<KnapsackSolver::SolverType>(Object x)
{
  std::string s = Symbol(x).str();
  if (s == "branch_and_bound") {
    return KnapsackSolver::KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER;
  } else {
    throw std::runtime_error("Unknown solver type: " + s);
  }
}

void init_bin_packing(Rice::Module& m) {
  Rice::define_class_under<KnapsackSolver>(m, "KnapsackSolver")
    .define_constructor(Rice::Constructor<KnapsackSolver, KnapsackSolver::SolverType, std::string>())
    .define_method("_solve", &KnapsackSolver::Solve)
    .define_method("best_solution_contains?", &KnapsackSolver::BestSolutionContains)
    .define_method(
      "init",
      [](KnapsackSolver& self, Array rb_values, Array rb_weights, Array rb_capacities) {
        std::vector<int64> values;
        for (std::size_t i = 0; i < rb_values.size(); ++i) {
          values.push_back(from_ruby<int64>(rb_values[i]));
        }

        std::vector<std::vector<int64>> weights;
        for (std::size_t i = 0; i < rb_weights.size(); ++i) {
          Array rb_w = Array(rb_weights[i]);
          std::vector<int64> w;
          for (std::size_t j = 0; j < rb_w.size(); ++j) {
            w.push_back(from_ruby<int64>(rb_w[j]));
          }
          weights.push_back(w);
        }

        std::vector<int64> capacities;
        for (std::size_t i = 0; i < rb_capacities.size(); ++i) {
          capacities.push_back(from_ruby<int64>(rb_capacities[i]));
        }

        self.Init(values, weights, capacities);
      });
}
