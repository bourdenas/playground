#include "algorithms.h"

#include <boost/algorithm/string/join.hpp>
#include <deque>
#include <iostream>
#include <map>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

#include "graph.h"

using namespace ranges;

void Bfs(const Graph& g, const std::string& v,
         std::function<bool(const Node&)> f_vertex,
         std::function<bool(const std::string& source,
                            const std::string& target, int weight)>
             f_edge,
         std::function<bool(const Node&)> f_post_vertex) {
  std::deque<const Node*> q = {&g.nodes.find(v)->second};
  std::set<std::string> seen = {g.nodes.find(v)->second.id};

  while (!q.empty()) {
    auto* node = q.front();
    q.pop_front();
    if (f_vertex(*node)) return;

    std::vector<std::string> discovered =
        node->edges | view::remove_if([&seen](const auto& edge) {
          return seen.find(edge.target) != seen.end();
        }) |
        view::transform([](const auto& edge) { return edge.target; });

    action::insert(seen, discovered);
    action::push_back(
        q, discovered | view::transform([&g](const auto& id) -> const Node* {
             const auto it = g.nodes.find(id);
             if (it != g.nodes.end()) return &it->second;
             return nullptr;
           }));

    for (const auto& edge : node->edges) {
      if (f_edge(node->id, edge.target, edge.weight)) return;
    }
    if (f_post_vertex(*node)) return;
  }
}

void Dfs(const Graph& g, const std::string& v,
         std::function<bool(const Node&)> f_vertex,
         std::function<bool(const std::string& source,
                            const std::string& target, int weight)>
             f_edge,
         std::function<bool(const Node&)> f_post_vertex) {
  std::deque<const Node*> q = {&g.nodes.find(v)->second};
  std::set<std::string> seen = {g.nodes.find(v)->second.id};

  while (!q.empty()) {
    auto* node = q.back();
    q.pop_back();
    if (f_vertex(*node)) return;

    std::vector<std::string> discovered =
        node->edges | view::remove_if([&seen](const auto& edge) {
          return seen.find(edge.target) != seen.end();
        }) |
        view::transform([](const auto& edge) { return edge.target; });

    action::insert(seen, discovered);
    action::push_back(q,
                      discovered | view::reverse |
                          view::transform([&g](const auto& id) -> const Node* {
                            const auto it = g.nodes.find(id);
                            if (it != g.nodes.end()) return &it->second;
                            return nullptr;
                          }));

    for (const auto& edge : node->edges) {
      if (f_edge(node->id, edge.target, edge.weight)) return;
    }
    if (f_post_vertex(*node)) return;
  }
}

void DfsRecursive(const Graph& g, const std::string& v,
                  std::function<bool(const Node&)> f_vertex,
                  std::function<bool(const std::string& source,
                                     const std::string& target, int weight)>
                      f_edge,
                  std::function<bool(const Node&)> f_post_vertex) {
  static std::set<std::string> seen;
  seen.insert(v);

  const auto& node = g.nodes.find(v)->second;
  if (f_vertex(node)) return;
  for (const auto& e : node.edges) {
    f_edge(node.id, e.target, e.weight);
    if (seen.find(e.target) == seen.end()) {
      DfsRecursive(g, e.target, f_vertex, f_edge, f_post_vertex);
    }
  }
}

namespace {
static auto noop_node = [](const Node&) { return false; };
static auto noop_edge = [](const std::string&, const std::string&, int) {
  return false;
};
};

void ConnectedComponents(const Graph& g) {
  std::vector<std::string> candidates =
      g.nodes | view::transform([](const auto& p) { return p.first; });

  while (!candidates.empty()) {
    std::set<std::string> members;

    Bfs(g, *candidates.begin(),
        [&members](const Node& node) {
          members.insert(node.id);
          return false;
        },
        noop_edge, noop_node);
    candidates |= action::remove_if([&members](const std::string& id) {
      return members.find(id) != members.end();
    });

    std::cout << "\nComponent: " << boost::algorithm::join(members, ", ");
  }
}

namespace {
enum class Colour {
  UNKNOWN = 0,
  RED = 1,
  BLUE = 2,
};
}  // namespace

bool IsBipartite(const Graph& g) {
  std::map<std::string, Colour> colour;

  const auto& node = g.nodes.begin()->second;
  colour[node.id] = Colour::RED;
  Bfs(g, node.id, noop_node,
      [&colour](const std::string& source, const std::string& target,
                int weight) {
        if (colour[source] == colour[target]) {
          colour[target] = Colour::UNKNOWN;
          return true;
        }
        colour[target] =
            colour[source] == Colour::RED ? Colour::BLUE : Colour::RED;
        return false;
      },
      noop_node);

  return colour.size() == g.nodes.size() &&
         std::none_of(colour.begin(), colour.end(), [](const auto& p) {
           return p.second == Colour::UNKNOWN;
         });
}

bool IsCyclic(const Graph& g) {
  std::map<std::string, std::string> parents;
  const auto& root = g.nodes.begin()->second;

  Dfs(g, root.id, noop_node,
      [&parents, &root](const std::string& source, const std::string& target,
                        int weight) {
        auto& parent = parents[target];
        if (!parent.empty() || target == root.id) {
          std::cout << "\nFound backedge '" << source << "' -> '" << target
                    << "'";
          return true;
        }
        parent = source;
        return false;
      },
      noop_node);
  return false;
}
