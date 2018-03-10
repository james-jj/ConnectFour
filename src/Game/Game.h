#ifndef Game_hpp
#define Game_hpp

#include "AIController.h"
#include "Board.h"
#include "Column.h"
#include "Player.h"

#include "gsl/gsl"

#include <stdio.h>

#include <tuple>
#include <vector>

#include <QObject>

/**
 * Game controls the game logic and stores the game state, for example,
 * the board, current players and their scores.
 */
class Game : public QObject {
  Q_OBJECT

 public:
  Game();

  void newGame();
  void restartGame();

  std::vector<unsigned int> getScores() const;
  int getCurrentPlayerID() const;
  Board& getBoard();

 signals:
  void reportWinSignal(int playerID,
                       std::vector<std::tuple<int, int>> winCoords) const;
  void reportCurrentPlayer(int playerID) const;

 public slots:
  /**
   * @brief takeTurn adds a disc to the selected column
   * @param selectedColumn: 0 based index of column
   */
  void takeTurn(int selectedColumn);

  /**
   * @brief turnController determines whether it is human or AI player's turn
   * (if AI is present) and takes the required turn, followed by AI player's
   * turn.
   * @param selectedColumn: 0 based index of column chosen by player
   */
  void turnController(int selectedColumn);

 private:
  struct PlayerInfo {
    Player player;
    unsigned int score{0};
    bool isAI{false};
  };
  AIController ai;
  Board board;
  std::vector<PlayerInfo> players;
  int currentPlayerIdx;
  int currentPlayerID;
  int difficulty{5};
  bool isFirstTurn{true};

  void initGame();
  bool isWon();
  bool isTurnValid(int selectedColumn) const;
  bool isInputInRange(int selectedColumn) const;
  bool isSpaceInColumn(int selectedColumn) const;
  void setFirstPlayer();
};

#endif /* Game_hpp */
