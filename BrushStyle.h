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

  const QBrush& set_brush(EStyle style)
  {
    current_style = style;
    return get_brush();
  }

  const QBrush& get_brush()
  {
    return styles[current_style];
  }

  EStyle get_style()
  {
    return current_style;
  }

  const QBrush& get_brush(EStyle style)
  {
    return styles[style];
  }

  BrushStyle(BrushStyle const &) = delete;
  BrushStyle &operator=(BrushStyle const &) = delete;

private:
  BrushStyle()
  {
    current_style = EStyle::Empty;
    styles[EStyle::Empty] = QBrush(Qt::black);
    styles[EStyle::Start] = QBrush(Qt::yellow);
    styles[EStyle::Obstacle] = QBrush(Qt::cyan);
    styles[EStyle::Stop] = QBrush(Qt::green);
  }

  EStyle current_style;
  std::unordered_map<EStyle, QBrush> styles;
};