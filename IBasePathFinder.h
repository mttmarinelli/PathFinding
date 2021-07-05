//
// Created by matteo on 04/07/21.
//
#include <QTimer>

#pragma once

class IBasePathFinder : public QObject
{
  typedef std::tuple<int, int> pos_t;
  virtual std::vector<pos_t> find(pos_t start, pos_t end, Grid &g);
};