#include <memory>
#include <QApplication>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <random>
#include <QMainWindow>
#include <iostream>
#include <QPropertyAnimation>
#include <QGraphicsWidget>
#include "GraphicsView.h"
#include "BrushStyle.h"
#include "ui_PathFindingWindow.h"

class Grid
{
public:
  class CellWidget : public QGraphicsRectItem
  {
  public:
    int r, c;
    explicit CellWidget(int _r = 0, int _c = 0, QGraphicsItem *parent = nullptr)
      : r(_r), c(_c), QGraphicsRectItem(parent) { setAcceptHoverEvents(true); }

  protected:
    const QBrush& getCellBrush() const
    {
      auto style = BrushStyle::instance();
      return brush() == style.get_current() ? style.get_style(BrushStyle::EStyle::Empty) : style.get_current();
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
      QGraphicsItem::mousePressEvent(event);
      setBrush(getCellBrush());
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
    {
      QGraphicsItem::hoverEnterEvent(event);
      setPen({{Qt::white}, 2, Qt::PenStyle::DotLine});
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
      QGraphicsItem::hoverLeaveEvent(event);
      setPen({QBrush(Qt::cyan), 1, Qt::SolidLine});
    }
  };

  float start_x{0.f};
  float start_y{0.f};
  int rows{10};
  int cols{10};
  float cell_width{50};
  float cell_height{50};
  float border_thickness{0};
  std::unique_ptr<std::unique_ptr<CellWidget>[]> data;

  [[nodiscard]] int ofs(int r, int c) const
  {
    const int pos = c + r * cols;
    if (pos < 0 || pos >= rows * cols)
      throw std::out_of_range("out of bounds");

    return pos;
  }

  Grid(float start_x, float start_y, int rows, int cols, int W, int H, float borderThickness = 0, QGraphicsScene *parent = nullptr) :
    start_x(start_x), start_y(start_y),
    rows(rows), cols(cols),
    border_thickness(borderThickness),
    data(new std::unique_ptr<CellWidget>[rows*cols])
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

  CellWidget* at(int r, int c) { return data[ofs(r, c)].get(); }

  [[nodiscard]] float x_coord(int c) const  { return start_x + c * (cell_width + border_thickness); }
  [[nodiscard]] float y_coord(int r) const  { return start_y + r * (cell_height + border_thickness); }
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  const auto border_style = QPen(QBrush(Qt::cyan), 1, Qt::SolidLine);
  const auto empty_brush = QBrush(Qt::black);
  const auto start_brush = QBrush(Qt::yellow);
  const auto stop_brush = QBrush(Qt::green);
  const auto obstacle_brush = QBrush(Qt::red);

  std::unique_ptr window = std::make_unique<QMainWindow>();
  std::unique_ptr main_window = std::make_unique<Ui::MainWindow>();
  window->setWindowTitle("QPathFinding");
  window->resize(850, 850);

  main_window->setupUi(window.get());

  const int R = 20, C = 30;
  const int W = 950, H = 700;

  std::random_device r;
  std::default_random_engine engine(r());
  std::uniform_int_distribution<int> uniform_dist(0, 100);

  std::unique_ptr scene = std::make_unique<QGraphicsScene>(0, 0, W, H, window.get());
  main_window->graphicsView->setScene(scene.get());

  Grid grid(10, 10, R, C, W, H, 3, scene.get());

  scene->setBackgroundBrush(empty_brush);

  QObject::connect(main_window->btnStartPos, &QPushButton::clicked, &a, [&](bool checked) {
    if (checked)
    {
      main_window->btnEndPos->setChecked(false);
      main_window->btnObstaclePos->setChecked(false);
      BrushStyle::instance().set_current(BrushStyle::EStyle::Start);
    }
  });

  QObject::connect(main_window->btnObstaclePos, &QPushButton::clicked, &a, [&](bool checked) {
    if (checked)
    {
      main_window->btnStartPos->setChecked(false);
      main_window->btnEndPos->setChecked(false);
      BrushStyle::instance().set_current(BrushStyle::EStyle::Obstacle);
    }
  });

  QObject::connect(main_window->btnEndPos, &QPushButton::clicked, &a, [&](bool checked) {
    if (checked)
    {
      main_window->btnStartPos->setChecked(false);
      main_window->btnObstaclePos->setChecked(false);
      BrushStyle::instance().set_current(BrushStyle::EStyle::Stop);
    }
  });

  std::unique_ptr timer = std::make_unique<QTimer>(nullptr);
  QObject::connect(timer.get(), &QTimer::timeout, &a, [&](){
    // game loop
  });

  timer->start(100);

  window->show();
  return QApplication::exec();
}
