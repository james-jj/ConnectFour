#include "application.h"

#include "GUIColumn.h"

#include <tuple>

#include <QObject>
#include <QThread>
#include <QTimer>

Application::Application() {
  connectSlotsSignals();
  game.reportCurrentPlayer(game.getCurrentPlayerID());
}

void Application::connectSlotsSignals() {
  // if AI is selected, then SLOT should be a function that takes turn (human),
  // calculates AI turn,  then takes AI turn (invoking game->takeTurn)
  for (auto& col : gui.getGUIBoard()->getColumns()) {
    QObject::connect(col, SIGNAL(clickedSignal(int)), &game,
                     SLOT(turnController(int)));
  }

  QObject::connect(
      &game.getBoard(), SIGNAL(discAddedSignal(int, int, Disc::Colour)),
      gui.getGUIBoard(), SLOT(addDiscToScene(int, int, Disc::Colour)),
      Qt::DirectConnection);
  qRegisterMetaType<std::vector<std::tuple<int, int>>>(
      "std::vector<std::tuple<int, int>>");
  QObject::connect(
      &game, SIGNAL(reportWinSignal(int, std::vector<std::tuple<int, int>>)),
      this, SLOT(handleWin(int, std::vector<std::tuple<int, int>>)),
      Qt::QueuedConnection);

  QObject::connect(gui.getRestartButton(), SIGNAL(clicked(bool)), this,
                   SLOT(newGame()));

  QObject::connect(&game, SIGNAL(reportCurrentPlayer(int)), &gui,
                   SLOT(updatePlayerTxt(int)));
}

void Application::handleWin(int playerID,
                            std::vector<std::tuple<int, int>> winCoords) {
  gui.drawWin(game.getScores(), winCoords);
}

void Application::newGame() {
  game.newGame();
  gui.clearScene();
  gui.updateScoreTxt(game.getScores());
}

void Application::restart() {
  gui.clearScene();
  game.restartGame();
}
