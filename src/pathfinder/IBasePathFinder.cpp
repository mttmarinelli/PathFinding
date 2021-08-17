//
// Created by matteo on 13/08/21.
//

#include <iostream>
#include <memory>

#include "IBasePathFinder.h"
#include "IFinderAlgorithm.h"

IBasePathFinder::IBasePathFinder(Grid &g)
{
  switch (PathFinderConfig::instance().type)
  {
    case PathFinderConfig::SerchType::DFS:
      finder = std::make_unique<DFSFinderAlgorithm>(g);
      break;

    case PathFinderConfig::SerchType::BFS:
      finder = std::make_unique<BFSFinderAlgorithm>(g);
      break;

    case PathFinderConfig::SerchType::Dijkstra:
      finder = std::make_unique<DijkstraFinderAlgorithm>(g);
      break;

    case PathFinderConfig::SerchType::A:
      finder = std::make_unique<AFinderAlgorithm>(g);
      break;

    default:
      finder.reset(nullptr);
  }
}

IBasePathFinder::~IBasePathFinder()
{
}

std::vector<IBasePathFinder::pos_t> IBasePathFinder::find() const
{
  if (!finder || !PathFinderConfig::instance().is_valid())
  {
    std::cout << "Please select a start/end position\n";
    return {};
  }

  pos_t start{PathFinderConfig::instance().start_pos->r, PathFinderConfig::instance().start_pos->c};
  pos_t end{PathFinderConfig::instance().end_pos->r, PathFinderConfig::instance().end_pos->c};

  return finder->find(start, end);
}
