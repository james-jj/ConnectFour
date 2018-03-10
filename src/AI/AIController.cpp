#include "AIController.h"
#include "Bitboard.h"
#include "Disc.h"
#include "TranspositionTable.h"

#include <iostream>
#include <vector>

AIController::AIController()
    : table(8388593) {  // 8388593 = 64mb transposition table)
  // populate column order so that middle columns are chosen first, and then
  // work outwards, e.g. order for 7 columns: 3,2,4,1,5,0,6.
  for (auto i = 0; i < nCols; ++i) {
    columnOrder.push_back(nCols / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2);
  }
}

int AIController::calculateNextMove(const Board& board, int movesRemaining,
                                    Disc::Colour aiColour) {
  table.reset();
  //  need to set up bit board as opposing player so that currentboard is
  //  correct
  Disc::Colour opposingColour;
  switch (aiColour) {
    case Disc::Colour::white:
      opposingColour = Disc::Colour::black;
      break;
    case Disc::Colour::black:
      opposingColour = Disc::Colour::white;
      break;
  }
  Bitboard bitBoard;
  bitBoard.convertToBitboard(board, opposingColour);
  bitBoard.updateBoard();  // switch to current player

  movesRemaining *= 2;  // moves remaining for each player combined

  int bestColumn{nRows / 2};
  int min{-(nCols * nRows - movesRemaining) / 2};
  int max{(nCols * nRows + 1 - movesRemaining) / 2};

  while (min < max) {  // iteratively narrow the min-max exploration window
    int med = min + (max - min) / 2;
    if (med <= 0 && min / 2 < med) {
      med = min / 2;
    } else if (med >= 0 && max / 2 > med) {
      med = max / 2;
    }
    // use a null depth window to know if the actual score is greater or
    // smaller than med
    int bestScore = negamax(bitBoard, movesRemaining, med, med + 1, bestColumn);
    if (bestScore <= med) {
      max = bestScore;
    } else {
      min = bestScore;
    }
  }
  return bestColumn;
}

int AIController::negamax(Bitboard board, int nMovesRemaining, int alpha,
                          int beta, int& bestColumn) {
  Expects(alpha < beta);
  // draw game
  if (nMovesRemaining == 0) {
    return 0;
  }
  // check for a win in each column
  for (auto i = 0; i < nCols; ++i) {
    if (board.canPlay(columnOrder[i])) {
      if (board.isWinningMove(columnOrder[i])) {
        bestColumn = columnOrder[i];
        return nMovesRemaining / 2;
      }
    }
  }
  //  set max possible score and check whether score for this board has already
  //  been calculated in the hash table, if score already calculated then update
  //  the max possible score
  int max{nMovesRemaining / 2};
  if (int val = table.get(board.createKey())) {
    max = val + minScore - 1;
  }
  //  prune search space with maximum possible scores
  if (beta > max) {
    beta = max;
    if (alpha >= beta) {
      return beta;
    }
  }
  //  search for highest scoring move on each available move, recurse to
  //  all available paths up to nMoves = 0, alternating between current player
  //  and opposing player.
  for (auto i = 0; i < nCols; ++i) {
    if (board.canPlay(columnOrder[i])) {
      int nextBestMove{0};
      Bitboard newBoard{board};
      newBoard.takeTurn(columnOrder[i]);
      int nMoves = nMovesRemaining;
      auto score{-negamax(newBoard, --nMoves, -beta, -alpha, nextBestMove)};
      if (score >= beta) {
        bestColumn = columnOrder[i];
        return score;
      }
      if (score > alpha) {
        alpha = score;
        bestColumn = columnOrder[i];
      }
    }
  }
  table.put(board.createKey(), alpha - minScore + 1);
  return alpha;
}