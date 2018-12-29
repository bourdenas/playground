#include <absl/strings/str_join.h>
#include <deque>
#include <iostream>
#include <map>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

#include "lib/algorithms.h"
#include "lib/backtracking.h"
#include "lib/graph.h"

using namespace ranges;

int main() {
  Graph g({
      Node("A",
           {
               Edge("B"),
               Edge("C"),
           }),
      Node("B",
           {
               Edge("A"),
               Edge("D"),
           }),
      Node("C",
           {
               Edge("A"),
           }),
      Node("D",
           {
               Edge("A"),
           }),

      Node("E",
           {
               Edge("F"),
           }),
      Node("F",
           {
               Edge("E"),
           }),
  });

  auto noop_node = [](const Node&) { return false; };
  auto noop_edge = [](const std::string&, const std::string&, int) {
    return false;
  };

  std::cout << "\nBFS(A): ";
  Bfs(g, "A",
      [](const Node& node) {
        std::cout << node.id << ", ";
        return false;
      },
      noop_edge, noop_node);

  std::cout << "\nBFS(D): ";
  Bfs(g, "D",
      [](const Node& node) {
        std::cout << node.id << ", ";
        return false;
      },
      noop_edge, noop_node);

  std::cout << "\nBFS(B): ";
  Bfs(g, "B",
      [](const Node& node) {
        std::cout << node.id << ", ";
        return false;
      },
      noop_edge, noop_node);

  std::cout << "\nDFS(A): ";
  Dfs(g, "A",
      [](const Node& node) {
        std::cout << node.id << ", ";
        return false;
      },
      noop_edge, noop_node);

  std::cout << "\nDFSR(A): ";
  DfsRecursive(g, "A",
               [](const Node& node) {
                 std::cout << node.id << ", ";
                 return false;
               },
               noop_edge, noop_node);

  ConnectedComponents(g);
  std::cout << "\nIsBipartite(g)=" << IsBipartite(g);
  std::cout << "\nIsCyclic(g)=" << IsCyclic(g);

  Graph g2({
      Node("A",
           {
               Edge("B"),
               Edge("C"),
           }),
      Node("B",
           {
               Edge("D"),
           }),
      Node("C",
           {
               Edge("A"),
           }),
      Node("D",
           {
               Edge("B"),
           }),
  });
  std::cout << "\n\nIsBipartite(g2)=" << IsBipartite(g2);
  std::cout << "\nIsCyclic(g2)=" << IsCyclic(g2);

  Graph g3({
      Node("A",
           {
               Edge("B"),
               Edge("C"),
           }),
      Node("B", {Edge("A")}),
      Node("C", {}),
  });
  std::cout << "\n\nIsBipartite(g3)=" << IsBipartite(g3);
  std::cout << "\nIsCyclic(g3)=" << IsCyclic(g3);

  const std::vector<std::string> input = {
      "A", "B", "C", "D", "E", "F",
  };
  const auto subsets_temp = ComputeSubsets(input);
  const std::vector<std::string> subsets =
      subsets_temp | view::transform([](const auto& subset) {
        return absl::StrJoin(subset, ",");
      });
  std::cout << "\n\nSubsets: " << subsets.size() << "\n";
  absl::StrJoin(subsets, "\n");

  const auto permutations_temp = ComputePermutations(input);
  const std::vector<std::string> permutations =
      permutations_temp | view::transform([](const auto& permutation) {
        return absl::StrJoin(permutation, ",");
      });
  std::cout << "\n\nPermutations: " << permutations.size() << "\n";
  absl::StrJoin(permutations, "\n");

  return 0;
}
