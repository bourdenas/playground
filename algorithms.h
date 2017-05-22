#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include <string>

#include "graph.h"

void Bfs(const Graph& g, const std::string& v,
         std::function<bool(const Node&)> f_vertex,
         std::function<bool(const std::string& source,
                            const std::string& target, int weight)> f_edge,
         std::function<bool(const Node&)> f_post_vertex);
void Dfs(const Graph& g, const std::string& v,
         std::function<bool(const Node&)> f_vertex,
         std::function<bool(const std::string& source,
                            const std::string& target, int weight)> f_edge,
         std::function<bool(const Node&)> f_post_vertex);
void DfsRecursive(const Graph& g, const std::string& v,
                  std::function<bool(const Node&)> f_vertex,
                  std::function<bool(const std::string& source,
                                     const std::string& target, int weight)>
                      f_edge,
                  std::function<bool(const Node&)> f_post_vertex);

void ConnectedComponents(const Graph& g);
bool IsBipartite(const Graph& g);
bool IsCyclic(const Graph& g);

#endif  // ALGORITHMS_H_
