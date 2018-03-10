#ifndef GUI_hpp
#define GUI_hpp

#include <tuple>
#include <vector>

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QWidget>

#include "GUIBoard.h"
#include "GUIColumn.h"
#include "Game.h"

/**
 * GUI draws the buttons, scores and current player text and also contains the
 * board.
 */
class GUI : public QWidget {
  Q_OBJECT
 public:
  GUI();

  /**
   * @brief clearScene removes all of the discs on the scene
   */
  void clearScene();

  /**
   * @brief updateScoreTxt
   * @param scores: 2 element vector containing score of each player
   */
  void updateScoreTxt(const std::vector<unsigned int>& scores);

  QSignalMapper* getButtonMapper() const;
  GUIBoard* getGUIBoard() const;
  QPushButton* getRestartButton() const;

 public slots:
  /**
   * @brief drawWin updates the scores displayed on the GUI
   * @param scores: 2 element vector containing scores: {Player1,Player2}
   */
  void drawWin(const std::vector<unsigned int>& scores,
               const std::vector<std::tuple<int, int>>& winCoords);

  /**
   * @brief updatePlayerTxt displays the current player on the GUI
   * @param playerID
   */
  void updatePlayerTxt(int playerID);

 private:
  QGraphicsView* view;
  QGraphicsScene* scene;
  GUIBoard* guiboard;
  QList<QPushButton*> buttons;
  QPushButton* restartButton;
  QSignalMapper* buttonMapper;
  QGraphicsTextItem* currentPlayerTxt;
  QGraphicsTextItem* scoreTxt;

  void addColumnButtons();
  void addRestartButton();
};

#endif /* GUI_hpp */
