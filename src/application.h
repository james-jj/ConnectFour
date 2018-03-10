#ifndef APPLICATION_H
#define APPLICATION_H

#include "GUI.h"
#include "Game.h"
#include "application.h"

#include <tuple>

#include <QObject>

/**
 * The Application stores the GUI and game states.
 * This is necessary to allow connection of
 * game and GUI slots and signals which enables use
 * of the QT signals and slots.
 */
class Application : public QObject {
  Q_OBJECT
 public:
  Application();

 public slots:
  /**
   * @brief handleWin updates GUI with win and restarts the game
   * @param playerID: ID of winning player
   * @param winCoords: 4 element vector of tuples containing {column,row}
   */
  void handleWin(int playerID, std::vector<std::tuple<int, int>> winCoords);
  /**
   * @brief restart clears GUI and board but keeps scores
   */
  void restart();
  /**
   * @brief newGame clears GUI and board and resets scores
   */
  void newGame();

 private:
  Game game;
  GUI gui;
  void connectSlotsSignals();
};

#endif  // APPLICATION_H
