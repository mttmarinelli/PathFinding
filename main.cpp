#include <memory>
#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QGraphicsScene>
#include <random>
#include <QMainWindow>
#include <iostream>
#include <QGraphicsWidget>
#include "Grid.h"
#include "BrushStyle.h"
#include "IBasePathFinder.h"
#include "ui_PathFindingWindow.h"

int main(int argc, char *argv[])
{
  typedef std::tuple<int, int> pos_t;
  QApplication a(argc, argv);

//  const auto border_style = QPen(QBrush(Qt::cyan), 1, Qt::SolidLine);
//  const auto empty_brush = QBrush(Qt::black);
//  const auto start_brush = QBrush(Qt::yellow);
//  const auto stop_brush = QBrush(Qt::green);
//  const auto obstacle_brush = QBrush(Qt::red);

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

  scene->setBackgroundBrush(Qt::black);
  BrushStyle::instance().set_brush(BrushStyle::EStyle::Start);

  QObject::connect(main_window->btnStartPos, QOverload<bool>::of(&QPushButton::clicked), [&](bool checked) {
    if (checked)
    {
      main_window->btnEndPos->setChecked(false);
      main_window->btnObstaclePos->setChecked(false);
      BrushStyle::instance().set_brush(BrushStyle::EStyle::Start);
    }
  });

  QObject::connect(main_window->btnObstaclePos, QOverload<bool>::of(&QPushButton::clicked), [&](bool checked) {
    if (checked)
    {
      main_window->btnStartPos->setChecked(false);
      main_window->btnEndPos->setChecked(false);
      BrushStyle::instance().set_brush(BrushStyle::EStyle::Obstacle);
    }
  });

  QObject::connect(main_window->btnEndPos, QOverload<bool>::of(&QPushButton::clicked), [&](bool checked) {
    if (checked)
    {
      main_window->btnStartPos->setChecked(false);
      main_window->btnObstaclePos->setChecked(false);
      BrushStyle::instance().set_brush(BrushStyle::EStyle::Stop);
    }
  });

  QObject::connect(main_window->cmbAlgorithm, QOverload<int>::of(&QComboBox::currentIndexChanged), &a, [&](int index) {
    PathFinderConfig::instance().type = static_cast<PathFinderConfig::SerchType>(index);
    std::cout << "Search Type: " << PathFinderConfig::instance().type_desc[PathFinderConfig::instance().type] << "\n";
  });

  std::unique_ptr timer = std::make_unique<QTimer>(nullptr);
  QObject::connect(timer.get(), &QTimer::timeout, &a, [&](){
    // game loop
  });

  timer->start(100);

  window->show();
  return QApplication::exec();
}
