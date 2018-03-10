#ifndef GUICOLUMN_H
#define GUICOLUMN_H

#include <QGraphicsRectItem>
#include <QObject>

class GUIColumn : public QObject, public QGraphicsRectItem {
  Q_OBJECT
 public:
  GUIColumn(int col);

  /**
   * @brief mousePressEvent emits clicked signal with the chosen column so
   * that slot knows which column was clicked on the board.
   * @param event
   */
  void mousePressEvent(QGraphicsSceneMouseEvent* event);

 signals:
  /**
   * @brief clickedSignal emitted on mousePressEvent
   * @param column: 0 based index of column
   */
  void clickedSignal(int column);

 private:
  const int column;
};

#endif  // GUICOLUMN_H
