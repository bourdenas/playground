#ifndef BACKTRACKING_H_
#define BACKTRACKING_H_

#include <string>
#include <vector>

// using namespace std;

std::vector<std::vector<std::string>>
    ComputeSubsets(const std::vector<std::string>& vec);
std::vector<std::vector<std::string>>
    ComputePermutations(const std::vector<std::string>& vec);

#endif  // BACKTRACKING_H_