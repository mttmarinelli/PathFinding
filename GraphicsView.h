#pragma once

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
  struct Movement
  {
    int vx{0}, vy{0};
  } movement;

public:
  explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

  [[nodiscard]] auto get_movement() const { return movement; }

protected:
  void keyPressEvent(QKeyEvent *event) override;
};
