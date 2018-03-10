#include "GUIBoard.h"
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>

#include <cmath>

#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include "GUI.h"
#include "GUIColumn.h"

GUIBoard::GUIBoard(QGraphicsScene *scene) {
  // create board
  int nCols{7};
  int nRows{6};

  // add grid squares to the board to hold the connect four discs
  for (int i = 0; i < nCols; ++i) {
    for (int j = 0; j < nRows; ++j) {
      QGraphicsRectItem *rect = new QGraphicsRectItem();
      rect->setRect(0, 0, 100, 100);
      rect->setPos(i * 100, (j + 1) * 100);
      scene->addItem(rect);
    }
    // add clickable columns
    GUIColumn *column = new GUIColumn(i);
    column->setRect(0, 0, 100, 600);
    column->setPos(i * 100, 100);
    column->setFlag(QGraphicsItem::ItemIsFocusable);
    column->setFocus();
    columns.push_back(column);
    scene->addItem(column);
  }
  currentScene = scene;  // store scene for future use
}

QList<QGraphicsEllipseItem *> GUIBoard::getDiscsOnScene() const {
  return discs;
}

QList<GUIColumn *> GUIBoard::getColumns() const { return columns; }

void GUIBoard::clear() { discs.clear(); }

void GUIBoard::addDiscToScene(int col, int row, Disc::Colour colour) {
  // draw a black/white disc at the requested location, wrt main window coords
  QGraphicsEllipseItem *disc;
  disc = new QGraphicsEllipseItem(0, 0, 90, 90);
  disc->setPos((100 * col) + 5, (100 * (6 - row) + 5));
  switch (colour) {
    case (Disc::Colour::black):
      disc->setBrush(QBrush(Qt::GlobalColor::yellow));
      break;

    case (Disc::Colour::white):
      disc->setBrush(QBrush(Qt::GlobalColor::red));
      break;
  }
  currentScene->addItem(disc);
  discs.append(disc);
}

void GUIBoard::drawConnectFour(
    const std::vector<std::tuple<int, int>> &winCoords) {
  std::unordered_map<int, int> mapCol;
  std::unordered_map<int, int> mapRow;
  for (const auto &pos : winCoords) {
    mapCol.insert({std::get<0>(pos), 1});
    mapRow.insert({std::get<1>(pos), 1});
  }
  //  find discs which are in the connect four and turn them black
  for (const auto &disc : discs) {
    auto col = static_cast<int>(floor(disc->pos().x() / 100));
    auto row = static_cast<int>(floor(disc->pos().y() / 100));
    // qDebug() << col << " " << row;
    if (mapCol[col] && mapRow[row]) {
      disc->setBrush(QBrush(Qt::GlobalColor::black));
    }
  }
}
