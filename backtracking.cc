#include "backtracking.h"

#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

namespace {
template <class T>
void Backtrack(
    const vector<T>& input, vector<T>& solution,
    function<bool(const vector<T>&, const vector<T>&)> is_solution,
    function<void(const vector<T>&, const vector<T>&)> process_solution,
    function<vector<T>(const vector<T>&, const vector<T>&)> create_candidates) {
  if (is_solution(input, solution)) {
    process_solution(input, solution);
    return;
  }

  const auto candidates = create_candidates(input, solution);
  for (const auto& candidate : candidates) {
    solution.push_back(candidate);
    // make_move(input, solution);
    Backtrack<T>(input, solution, is_solution, process_solution,
                 create_candidates);
    // undo_move(input, solution);
    solution.pop_back();
  }
}
}  // namespace

vector<vector<string>> ComputeSubsets(const vector<string>& vec) {
  vector<vector<string>> subsets;
  Backtrack<string>(
      vec, vector<string>(),
      [](const auto& input, const auto& solution) {
        return input.size() == solution.size();
      },
      [&subsets](const auto& input, const auto& solution) {
        subsets.push_back(solution | view::remove_if([](const string& e) {
                            return e.empty();
                          }));
      },
      [](const auto& input, const auto& solution) {
        auto next_elem = solution.size();
        return vector<string>({input[next_elem], string()});
      });

  return subsets;
}

vector<vector<string>> ComputePermutations(const vector<string>& vec) {
  vector<vector<string>> permutations;
  Backtrack<string>(
      vec, vector<string>(),
      [](const auto& input, const auto& solution) {
        return input.size() == solution.size();
      },
      [&permutations](const auto& input, const auto& solution) {
        permutations.push_back(solution);
      },
      [](const auto& input, const auto& solution) {
        const std::set<string> sol_set(solution.begin(), solution.end());
        return vector<string>(input |
                              view::remove_if([&sol_set](const string& e) {
                                return sol_set.find(e) != sol_set.end();
                              }));
      });

  return permutations;
}

// vector<vector<int>>