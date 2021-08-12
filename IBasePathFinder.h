//
// Created by matteo on 04/07/21.
//

#pragma once

#include "Grid.h"

class PathFinderConfig
{
  PathFinderConfig() : start_pos{nullptr}, end_pos{nullptr}, type{SerchType::DFS}
  {
    type_desc[SerchType::DFS] = "DSF";
    type_desc[SerchType::BFS] = "BSF";
    type_desc[SerchType::Dijkstra] = "Dijkstra";
    type_desc[SerchType::A] = "A*";
  }

public:
  enum class SerchType {
    DFS,
    BFS,
    Dijkstra,
    A
  };

  static PathFinderConfig& instance()
  {
    static PathFinderConfig data;
    return data;
  }

  Grid::CellWidget *start_pos, *end_pos;
  SerchType type;
  std::unordered_map<SerchType, std::string> type_desc;

  PathFinderConfig(PathFinderConfig const &) = delete;
  PathFinderConfig& operator=(PathFinderConfig const &) = delete;
};

class IBasePathFinder : public QObject
{
  typedef std::tuple<int, int> pos_t;
  virtual std::vector<pos_t> find(pos_t start, pos_t end, Grid &g);
};