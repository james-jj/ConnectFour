#ifndef GUIBOARD_H
#define GUIBOARD_H

#include "Disc.h"
#include "GUIColumn.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QList>
#include <QObject>

class GUIBoard : public QObject {
  Q_OBJECT
 public:
  GUIBoard(QGraphicsScene *newScene);

  /**
   * @brief clear clears all discs from the scene
   */
  void clear();

  QList<QGraphicsEllipseItem *> getDiscsOnScene() const;
  QList<GUIColumn *> getColumns() const;

 public slots:
  /**
   * @brief addDiscToScene draws a disc on the GUI board
   * @param col: 0 based column index to draw disc at
   * @param row: 0 based row index to draw disc at
   * @param colour: colour of the disc
   */
  void addDiscToScene(int col, int row, Disc::Colour colour);

  /**
   * @brief drawConnectFour draws x's on the four connecting discs
   * @param winCoords: 4 element vector of tuples containing {column,row}
   */
  void drawConnectFour(const std::vector<std::tuple<int, int>> &winCoords);

 private:
  QGraphicsScene *currentScene;
  QList<QGraphicsEllipseItem *> discs;
  QList<GUIColumn *> columns;
};

#endif  // GUIBOARD_H
