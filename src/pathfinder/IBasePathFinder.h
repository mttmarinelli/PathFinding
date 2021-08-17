//
// Created by matteo on 04/07/21.
//

#pragma once

#include "../ui/Grid.h"

class IFinderAlgorithm;

class PathFinderConfig
{
  PathFinderConfig()
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

  Grid::CellWidget *start_pos = nullptr;
  Grid::CellWidget *end_pos = nullptr;
  SerchType type = SerchType::DFS;
  std::unordered_map<SerchType, std::string> type_desc;

  bool is_valid() const
  {
    return start_pos && end_pos;
  }

  void clear()
  {
    start_pos = nullptr;
    end_pos = nullptr;
  }

  PathFinderConfig(PathFinderConfig const &) = delete;
  PathFinderConfig& operator=(PathFinderConfig const &) = delete;
};

class IBasePathFinder
{
  using pos_t = std::tuple<int, int>;
  std::unique_ptr<IFinderAlgorithm> finder;

public:
  explicit IBasePathFinder(Grid &g);
  ~IBasePathFinder();
  [[nodiscard]] std::vector<pos_t> find() const;
};