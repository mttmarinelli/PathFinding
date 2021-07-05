//
// Created by matteo on 26/06/21.
//

#include <QKeyEvent>
#include "GraphicsView.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
  QGraphicsView::keyPressEvent(event);

  switch (event->key())
  {
    case Qt::Key_Up:
      movement.vx = 0;
      movement.vy = -1;
      break;
    case Qt::Key_Down:
      movement.vx = 0;
      movement.vy = 1;
      break;
    case Qt::Key_Left:
      movement.vx = -1;
      movement.vy = 0;
      break;
    case Qt::Key_Right:
      movement.vx = 1;
      movement.vy = 0;
      break;
  }
}
