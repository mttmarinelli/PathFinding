//
// Created by matteo on 13/08/21.
//

#include "IFinderAlgorithm.h"
#include "../ui/Grid.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

#include <QGraphicsScene>

IFinderAlgorithm::IFinderAlgorithm(Grid &g) : grid(g)
{
  build_graph();
}

void IFinderAlgorithm::build_graph()
{
  const auto R = grid.rows;
  const auto C = grid.cols;
  graph = std::vector<std::vector<GraphNode>>(R, std::vector<GraphNode>(C));

  const auto obstacle_brush = BrushStyle::instance().get_brush(BrushStyle::EStyle::Obstacle);

  for (auto r = 0; r < R; r++)
  for (auto c = 0; c < C; c++)
  {
    graph[r][c].r = r;
    graph[r][c].c = c;

    if (grid.at(r, c)->brush() == obstacle_brush)
      graph[r][c].state = GraphNode::NodeState::visited;
  }
}

bool IFinderAlgorithm::is_valid_cell(int r, int c, bool skip_in_process)
{
  auto is_bounded = [&](int lr, int lc) {
    const auto R = static_cast<int>(graph.size());
    const auto C = static_cast<int>(graph[0].size());

    return lr >= 0 && lr < R && lc >= 0 && lc < C;
  };

  // out of bounds
  if (!is_bounded(r, c))
    return false;

  return graph[r][c].state == GraphNode::NodeState::unvisited || (!skip_in_process && graph[r][c].state == GraphNode::NodeState::processing);
}

void IFinderAlgorithm::visit_cell(GraphNode *p)
{
  p->state = GraphNode::NodeState::visited;

  if (const auto &style = grid.at(p->r, p->c)->brush();
      style == BrushStyle::instance().get_brush(BrushStyle::EStyle::Start) ||
      style == BrushStyle::instance().get_brush(BrushStyle::EStyle::Stop))
    return;

  grid.at(p->r, p->c)->setBrush(BrushStyle::instance().get_brush(BrushStyle::EStyle::Visited));
}

IFinderAlgorithm::vec_pos_t IFinderAlgorithm::build_path(const GraphNode *end) const
{
  if (!end->coming_from)
    return {};

  GraphNode *n = const_cast<GraphNode *>(end);

  vec_pos_t pos_path;

  while (n)
  {
    pos_path.push_back({n->r, n->c});
    n = n->coming_from;
  }

  std::ranges::reverse(pos_path);
  return pos_path;
}

DFSFinderAlgorithm::DFSFinderAlgorithm(Grid &g) : IFinderAlgorithm(g)
{
}

std::vector<IFinderAlgorithm::pos_t> DFSFinderAlgorithm::find(IFinderAlgorithm::pos_t start, IFinderAlgorithm::pos_t end)
{
  auto start_node = &graph[std::get<0>(start)][std::get<1>(start)];
  auto end_node = &graph[std::get<0>(end)][std::get<1>(end)];

  std::cout << "DFS Search Algorithm is running:\n"
               "\tstart:\t " << start_node->r+1 << "\t" << start_node->c+1 << "\n"
               "\tend:\t " << end_node->r+1 << "\t" << end_node->c+1 << "\n";

  std::stack<GraphNode*> frontier;
  frontier.push(start_node);

  auto expand = [&](GraphNode *p) {
    const auto r0 = p->r-1;
    const auto r1 = p->r+1;
    const auto c0 = p->c-1;
    const auto c1 = p->c+1;

    auto check_path = [&](int r, int c) {
      if (!is_valid_cell(r, c))
        return;

      graph[r][c].state = GraphNode::NodeState::processing;
      graph[r][c].coming_from = p;

      frontier.push(&graph[r][c]);
    };

    check_path(p->r, c0);
    check_path(r0, p->c);
    check_path(p->r, c1);
    check_path(r1, p->c);
  };

  while(!frontier.empty())
  {
    const auto p = frontier.top();
    frontier.pop();

    if (p == end_node)
      break;

    visit_cell(p);
    expand(p);
  }

  return build_path(end_node);
}

BFSFinderAlgorithm::BFSFinderAlgorithm(Grid &g) : IFinderAlgorithm(g)
{
}

std::vector<IFinderAlgorithm::pos_t> BFSFinderAlgorithm::find(IFinderAlgorithm::pos_t start, IFinderAlgorithm::pos_t end)
{
  auto start_node = &graph[std::get<0>(start)][std::get<1>(start)];
  auto end_node = &graph[std::get<0>(end)][std::get<1>(end)];

  std::cout << "BFS Search Algorithm is running:\n"
               "\tstart:\t " << start_node->r+1 << "\t" << start_node->c+1 << "\n"
               "\tend:\t " << end_node->r+1 << "\t" << end_node->c+1 << "\n";

  std::queue<GraphNode*> frontier;
  frontier.push(start_node);

  auto expand = [&](GraphNode *p) {
    const auto r0 = p->r-1;
    const auto r1 = p->r+1;
    const auto c0 = p->c-1;
    const auto c1 = p->c+1;

    auto check_path = [&](int r, int c) {
      if (!is_valid_cell(r, c))
        return;

      graph[r][c].state = GraphNode::NodeState::processing;
      graph[r][c].coming_from = p;
      frontier.push(&graph[r][c]);
    };

    check_path(r1, p->c);
    check_path(p->r, c1);
    check_path(r0, p->c);
    check_path(p->r, c0);
  };

  while(!frontier.empty())
  {
    const auto p = frontier.front();
    frontier.pop();

    if (p == end_node)
      break;

    visit_cell(p);
    expand(p);
  }

  return build_path(end_node);
}

DijkstraFinderAlgorithm::DijkstraFinderAlgorithm(Grid &g) : IFinderAlgorithm(g)
{
}

std::vector<IFinderAlgorithm::pos_t> DijkstraFinderAlgorithm::find(IFinderAlgorithm::pos_t start, IFinderAlgorithm::pos_t end)
{
  auto start_node = &graph[std::get<0>(start)][std::get<1>(start)];
  auto end_node = &graph[std::get<0>(end)][std::get<1>(end)];

  std::cout << "Dijkstra Search Algorithm is running:\n"
               "\tstart:\t " << start_node->r+1 << "\t" << start_node->c+1 << "\n"
               "\tend:\t " << end_node->r+1 << "\t" << end_node->c+1 << "\n";

  // TODO: replace the deque data structure with a MinHeap
  std::deque<GraphNode*> frontier;
  frontier.push_back(start_node);
  start_node->distance = 0;

  auto expand = [&](GraphNode *p) {
    const auto r0 = p->r-1;
    const auto r1 = p->r+1;
    const auto c0 = p->c-1;
    const auto c1 = p->c+1;

    path_node_t neighbors;

    auto check_path = [&](int r, int c) {
      if (!is_valid_cell(r, c))
        return;

      graph[r][c].state = GraphNode::NodeState::processing;
      neighbors.push_back(&graph[r][c]);
    };

    check_path(r1, p->c);
    check_path(p->r, c1);
    check_path(r0, p->c);
    check_path(p->r, c0);

    return neighbors;
  };

  while(!frontier.empty())
  {
    const auto p = frontier.front();
    frontier.pop_front();

    if (p == end_node)
      break;

    if (p->distance == std::numeric_limits<int>::max())
      return {};

    visit_cell(p);

    // direction from which the algorithm reached the current node
    const int direction_r = p->coming_from ? std::abs(p->coming_from->r - p->r) : 0;
    const int direction_c = p->coming_from ? std::abs(p->coming_from->c - p->c) : 0;

    for (auto n : expand(p))
    {
      // additional weight added to any turn performed relative to the travelling direction
      const int move_weight = direction_c * std::abs(p->r - n->r) + direction_r * std::abs(p->c - n->c);
      if (const int dist = p->distance + n->weight + move_weight; dist < n->distance)
      {
        n->distance = dist;
        n->coming_from = p;
      }

      frontier.push_back(n);
    }

    std::ranges::sort(frontier, [](const GraphNode *n1, const GraphNode *n2) {
      return n1->distance < n2->distance;
    });
  }

  return build_path(end_node);
}

AFinderAlgorithm::AFinderAlgorithm(Grid &g) : IFinderAlgorithm(g)
{
}

std::vector<IFinderAlgorithm::pos_t> AFinderAlgorithm::find(IFinderAlgorithm::pos_t start, IFinderAlgorithm::pos_t end)
{
  auto start_node = &graph[std::get<0>(start)][std::get<1>(start)];
  auto end_node = &graph[std::get<0>(end)][std::get<1>(end)];

  std::cout << "A* Search Algorithm is running:\n"
               "\tstart:\t " << start_node->r+1 << "\t" << start_node->c+1 << "\n"
               "\tend:\t " << end_node->r+1 << "\t" << end_node->c+1 << "\n";

  // TODO: replace the deque data structure with a MinHeap
  std::deque<GraphNode*> frontier;
  frontier.push_back(start_node);
  update_node_distance(start_node, nullptr, end_node);

  auto expand = [&](GraphNode *p) {
    const auto r0 = p->r-1;
    const auto r1 = p->r+1;
    const auto c0 = p->c-1;
    const auto c1 = p->c+1;

    auto check_path = [&](int r, int c) {
      if (!is_valid_cell(r, c, false))
        return;

      const bool in_process = graph[r][c].state == GraphNode::NodeState::processing;

      graph[r][c].state = GraphNode::NodeState::processing;

      if (!update_node_distance(&graph[r][c], p, end_node) || in_process)
        return;

      frontier.push_back(&graph[r][c]);
    };

    check_path(r1, p->c);
    check_path(p->r, c1);
    check_path(r0, p->c);
    check_path(p->r, c0);
  };

  int cnt = 0;
  while(!frontier.empty())
  {
    const auto p = frontier.front();
    frontier.pop_front();

    const std::string str = std::to_string(cnt++) + " [" + std::to_string(p->estimated_distance) + ", " + std::to_string(p->distance) + "]";
//    auto text = grid.at(p->r, p->c)->scene()->addText(QString::fromStdString(str));
//    auto rect = grid.at(p->r, p->c)->rect();
//    text->setPos(rect.center().x() - rect.width()/2, rect.center().y() - rect.height()/2);
//    text->setTextWidth(100);
//    text->setOpacity(1);

    std::cout << "[" << p->r << ", " << p->c << "]: " << str << "\n";

    if (p == end_node)
      break;

    if (p->distance == std::numeric_limits<int>::max())
      return {};

    visit_cell(p);
    expand(p);

    std::ranges::sort(frontier, [](const GraphNode *n1, const GraphNode *n2) {
      if (n1->estimated_distance < n2->estimated_distance)
        return true;

      if (n1->estimated_distance > n2->estimated_distance)
        return false;

      return n1->distance < n2->distance;
    });
  }

  return build_path(end_node);
}

int AFinderAlgorithm::heuristic_distance(const IFinderAlgorithm::GraphNode *p1, const IFinderAlgorithm::GraphNode *p2) const
{
  if (!p1 || !p2)
    return std::numeric_limits<int>::max();

  return std::abs(p2->r - p1->r) + std::abs(p2->c - p1->c);
}

bool AFinderAlgorithm::update_node_distance(IFinderAlgorithm::GraphNode *node, IFinderAlgorithm::GraphNode *prev, const IFinderAlgorithm::GraphNode *end)
{
  // direction from which the algorithm reached the current node
  const bool build_direction = prev && prev->coming_from;
  const int direction_r = build_direction ? std::abs(prev->coming_from->r - prev->r) : 0;
  const int direction_c = build_direction ? std::abs(prev->coming_from->c - prev->c) : 0;
  const int move_weight = build_direction ? node->weight + direction_c * std::abs(prev->r - node->r) + direction_r * std::abs(prev->c - node->c) : prev ? node->weight : 0;

  if (prev && prev->distance+move_weight >= node->distance)
    return false;

  node->distance = prev ? prev->distance+move_weight : move_weight;
  node->estimated_distance = node->distance + heuristic_distance(node, end);
  node->coming_from = prev;

  return true;
}
