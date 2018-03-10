#include "GUIColumn.h"

GUIColumn::GUIColumn(int col) : column(col) {}

void GUIColumn::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  emit clickedSignal(column);
}
