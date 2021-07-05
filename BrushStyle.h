//
// Created by matteo on 30/06/21.
//

#pragma once

#include <QBrush>
#include <unordered_map>

class BrushStyle
{
public:
  enum class EStyle {
    Empty,
    Start,
    Obstacle,
    Stop
  };

  static BrushStyle& instance()
  {
    static BrushStyle brush;
    return brush;
  }

  const QBrush& set_current(EStyle style)
  {
    current_style = style;
    return get_current();
  }

  const QBrush& get_current()
  {
    return styles[current_style];
  }

  const QBrush& get_style(EStyle style)
  {
    return styles[style];
  }

private:
  BrushStyle()
  {
    styles[EStyle::Empty] = QBrush(Qt::black);
    styles[EStyle::Start] = QBrush(Qt::yellow);
    styles[EStyle::Obstacle] = QBrush(Qt::cyan);
    styles[EStyle::Stop] = QBrush(Qt::green);
  }

  static BrushStyle brush;

  EStyle current_style;
  std::unordered_map<EStyle, QBrush> styles;
};