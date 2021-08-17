//
// Created by matteo on 13/08/21.
//

#pragma once

#include <tuple>
#include <string>
#include <vector>

class Grid;

class IFinderAlgorithm
{
public:
  struct GraphNode {
    enum class NodeState {
      unvisited = 0,
      processing,
      visited
    };

    int r = -1;
    int c = -1;
    int weight = 1; // node weight
    int distance = std::numeric_limits<int>::max(); // current distance from start point
    int estimated_distance = std::numeric_limits<int>::max(); // estimated distance to end node
    NodeState state = NodeState::unvisited;
    GraphNode *coming_from = nullptr;
  };

  using pos_t = std::tuple<int, int>;
  using vec_pos_t = std::vector<pos_t>;
  using path_node_t = std::vector<GraphNode*>;

  explicit IFinderAlgorithm(Grid &g);
  virtual ~IFinderAlgorithm() = default;
  virtual vec_pos_t find(pos_t start, pos_t end) = 0;

protected:

  Grid &grid;
  std::vector<std::vector<GraphNode>> graph;

  [[nodiscard]] std::string to_string(const std::string &nm, pos_t start, pos_t end) const;

  void build_graph();

  [[nodiscard]] bool is_valid_cell(int r, int c, bool skip_in_process = true);
  void visit_cell(GraphNode *p);
  vec_pos_t build_path(const GraphNode *end) const;
};

inline bool operator==(const IFinderAlgorithm::GraphNode& lhs, const IFinderAlgorithm::GraphNode& rhs)
{
  return lhs.r == rhs.r && lhs.c == rhs.c;
}

inline bool operator==(const IFinderAlgorithm::pos_t& lhs, const IFinderAlgorithm::GraphNode& rhs)
{
  const auto [r, c] = lhs;
  return r == rhs.r && c == rhs.c;
}

class DFSFinderAlgorithm : public IFinderAlgorithm
{
public:
  explicit DFSFinderAlgorithm(Grid &g);
  std::vector<pos_t> find(pos_t start, pos_t end) override;
};

class BFSFinderAlgorithm : public IFinderAlgorithm
{
public:
  explicit BFSFinderAlgorithm(Grid &g);
  std::vector<pos_t> find(pos_t start, pos_t end) override;
};

class DijkstraFinderAlgorithm : public IFinderAlgorithm
{
public:
  explicit DijkstraFinderAlgorithm(Grid &g);
  std::vector<pos_t> find(pos_t start, pos_t end) override;
};

class AFinderAlgorithm : public IFinderAlgorithm
{
  int heuristic_distance(const GraphNode *p1, const GraphNode *p2) const;
  bool update_node_distance(GraphNode *node, GraphNode *prev, const GraphNode *end);
public:
  explicit AFinderAlgorithm(Grid &g);
  std::vector<pos_t> find(pos_t start, pos_t end) override;
};
