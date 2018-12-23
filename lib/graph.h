#ifndef GRAPH_H_
#define GRAPH_H_

#include <map>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

struct Edge {
  Edge(const std::string& target, int weight = 0)
      : target(target), weight(weight) {}

  std::string target;
  int weight;
};

struct Node {
  Node(const std::string& id, const std::vector<Edge>& edges)
      : id(id), edges(edges) {}

  std::string id;
  std::vector<Edge> edges;
};

struct Graph {
  Graph(const std::vector<Node>& input) {
    nodes = input | ranges::view::transform([](const auto& node) {
              return std::make_pair(node.id, node);
            });
  }

  std::map<std::string, Node> nodes;
};

#endif  // GRAPH_H_