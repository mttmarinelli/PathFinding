#include <memory>
#include <random>
#include <thread>
#include <iostream>
#include <fmt/core.h>

#include <QApplication>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

#include "ui/BrushStyle.h"
#include "ui/Grid.h"
#include "ui/ui_PathFindingWindow.h"
#include "utility/Logger.h"
#include "pathfinder/IBasePathFinder.h"

// TODO: add the possibility to change the node weight
// TODO: animate the search process

int main(int argc, char *argv[])
{
  const int R = 15;
  const int C = 25;
  const int W = 1500;
  const int H = 800;
  const int pad = 100;
  const int graphics_refresh_time_ms = 25;

  QApplication a(argc, argv);

  auto window = std::make_unique<QMainWindow>();
  auto main_window = std::make_unique<Ui::MainWindow>();

  window->setWindowTitle("QPathFinding");
  main_window->setupUi(window.get());
  window->resize(W+pad, H+pad);

  auto scene = std::make_unique<QGraphicsScene>(0, 0, W, H, window.get());
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
    Logger::push(Logger::LogType::Info, fmt::format("Search Type: {}", PathFinderConfig::instance().type_desc[PathFinderConfig::instance().type]));
  });

  QObject::connect(main_window->btnPlay, QOverload<bool>::of(&QPushButton::clicked), [&](bool) {

    auto &brush = BrushStyle::instance();
    auto &config = PathFinderConfig::instance();

    if (!config.is_valid())
    {
      Logger::push(Logger::LogType::Warning, "Please, select a valid start/end position");
      return;
    }

    const int start_r = config.start_pos->r;
    const int start_c = config.start_pos->c;
    const int end_r = config.end_pos->r;
    const int end_c = config.end_pos->c;

    auto cell_has_brush = [&](int r, int c, BrushStyle::EStyle style) {
      return grid.at(r, c)->brush() == brush.get_brush(style);
    };

    for (int r = 0; r < grid.rows; r++)
    for (int c = 0; c < grid.cols; c++)
      if (cell_has_brush(r, c, BrushStyle::EStyle::Visited) ||
          cell_has_brush(r, c, BrushStyle::EStyle::Path))
        grid.at(r, c)->setBrush(brush.get_brush(BrushStyle::EStyle::Empty));

    IBasePathFinder finder{grid};
    int nodes = 0;
    for (auto [r, c] : finder.find())
    {
      if ((r == start_r && c == start_c) || (r == end_r && c == end_c))
        continue;

      grid.at(r, c)->setBrush(brush.get_brush(BrushStyle::EStyle::Path));
      std::this_thread::sleep_for(std::chrono::milliseconds(graphics_refresh_time_ms));
      scene->update();
      QApplication::processEvents();
      nodes++;
    }

    main_window->statusbar->showMessage(QString::fromStdString("Number of nodes in the path: " + std::to_string(nodes)));
  });

  QObject::connect(main_window->btnClear, QOverload<bool>::of(&QPushButton::clicked), [&](bool) {
    grid.clear();
    PathFinderConfig::instance().clear();
  });

  window->show();
  return QApplication::exec();
}
