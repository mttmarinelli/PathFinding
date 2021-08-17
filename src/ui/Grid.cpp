//
// Created by matteo on 05/07/21.
//

#include "Grid.h"
#include "../pathfinder/IBasePathFinder.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

Grid::CellWidget::CellWidget(int _r, int _c, QGraphicsItem *parent) : r(_r), c(_c), QGraphicsRectItem(parent)
{
  setAcceptHoverEvents(true);
}

const QBrush &Grid::CellWidget::getCellBrush() const
{
  auto &style = BrushStyle::instance();
  return brush() == style.get_brush() ? style.get_brush(BrushStyle::EStyle::Empty) : style.get_brush();
}

void Grid::CellWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mousePressEvent(event);
  setBrush(getCellBrush());

  auto &style = BrushStyle::instance();

  switch (style.get_style())
  {
    case BrushStyle::EStyle::Start:
    {
      auto &start = PathFinderConfig::instance().start_pos;

      if (!start)
        start = this;
      else
      {
        start->setBrush(style.get_brush(BrushStyle::EStyle::Empty));
        start = start != this ? this : nullptr;
      }
    } break;

    case BrushStyle::EStyle::Stop:
    {
      auto &end = PathFinderConfig::instance().end_pos;

      if (!end)
        end = this;
      else
      {
        end->setBrush(style.get_brush(BrushStyle::EStyle::Empty));
        end = end != this ? this : nullptr;
      }
    } break;

    default:
      return;
  }
}

void Grid::CellWidget::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  QGraphicsItem::hoverEnterEvent(event);
  setPen({{Qt::white}, 2, Qt::PenStyle::DotLine});
}

void Grid::CellWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  QGraphicsItem::hoverLeaveEvent(event);
  setPen({QBrush(Qt::cyan), 1, Qt::SolidLine});
}

int Grid::ofs(int r, int c) const
{
  const int pos = c + r * cols;
  if (pos < 0 || pos >= rows * cols)
    throw std::out_of_range("out of bounds");

  return pos;
}

Grid::Grid(float start_x, float start_y, int rows, int cols, int W, int H, float borderThickness, QGraphicsScene *parent) :
  start_x(start_x), start_y(start_y),
  rows(rows), cols(cols),
  border_thickness(borderThickness),
  data(rows*cols)
{
  cell_width = (W - (2 * start_x)) / cols - border_thickness;
  cell_height = (H - (2 * start_y)) / rows - border_thickness;

  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
    {
      data[ofs(r, c)] = std::make_unique<CellWidget>(r, c);
      data[ofs(r, c)]->setRect(x_coord(c), y_coord(r), cell_width, cell_height);
      data[ofs(r, c)]->setBrush(Qt::black);
      data[ofs(r, c)]->setPen({QBrush(Qt::cyan), 1, Qt::SolidLine});
      parent->addItem(static_cast<QGraphicsRectItem*>(data[ofs(r, c)].get()));
    }
}

void Grid::clear()
{
  for (auto &c : data)
    c->setBrush(BrushStyle::instance().get_brush(BrushStyle::EStyle::Empty));
}


Grid::CellWidget* Grid::at(int r, int c) { return data[ofs(r, c)].get(); }

float Grid::x_coord(int c) const  { return start_x + c * (cell_width + border_thickness); }
float Grid::y_coord(int r) const  { return start_y + r * (cell_height + border_thickness); }