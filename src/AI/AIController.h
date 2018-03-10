#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <gsl/gsl>

#include "Bitboard.h"
#include "Board.h"
#include "TranspositionTable.h"

class AIController {
 public:
  AIController();
  AIController(int _difficulty, std::tuple<int, int> boardSize);

  /**
   * @brief calculateNextMove uses negamax algorithm to calculate next move
   * @param board
   * @param movesRemaining: controls depth of solver/difficulty
   * @param aiColour
   * @return 0 based column index chosen by negamax algorithm
   */
  int calculateNextMove(const Board& board, int movesRemaining,
                        Disc::Colour aiColour);

 private:
  const int nCols{7};  // board width
  const int nRows{6};  // board height
  const int minScore{-(7 * 6) / 2 + 3};
  const int maxScore{(7 * 6 + 1) / 2 - 3};
  TranspositionTable table;
  std::vector<int> columnOrder;

  int negamax(Bitboard board, int nMovesRemaining, int alpha, int beta,
              int& bestColumn);
};

#endif  // AICONTROLLER_H
