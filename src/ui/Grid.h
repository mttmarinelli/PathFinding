//
// Created by matteo on 05/07/21.
//

#pragma once

#include "BrushStyle.h"
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPen>
#include <memory>

class Grid
{
public:
  class CellWidget : public QGraphicsRectItem
  {
  public:
    int r, c;
    explicit CellWidget(int _r = 0, int _c = 0, QGraphicsItem *parent = nullptr);

  protected:
    [[nodiscard]] const QBrush& getCellBrush() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
  };

  float start_x{0.f};
  float start_y{0.f};
  int rows{10};
  int cols{10};
  float cell_width{50};
  float cell_height{50};
  float border_thickness{0};
  std::vector<std::unique_ptr<CellWidget>> data;

  [[nodiscard]] int ofs(int r, int c) const;

  Grid(float start_x, float start_y, int rows, int cols, int W, int H, float borderThickness = 0, QGraphicsScene *parent = nullptr);

  CellWidget* at(int r, int c);

  void clear();

  [[nodiscard]] float x_coord(int c) const;
  [[nodiscard]] float y_coord(int r) const;
};
