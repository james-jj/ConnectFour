#include "Bitboard.h"

#include <bitset>
#include <iostream>

#include <cmath>

void Bitboard::takeTurn(int col) {
  if (!canPlay(col)) {
    return;
  }
  currentBoard ^= mask;            // switch players
  mask |= mask + bottomMask(col);  // add disc
}

void Bitboard::reverseTurn(int col) {
  mask |= mask - bottomMask(col);  // remove disc
  currentBoard ^= mask;            // switch players
}

void Bitboard::addDisc(int col) {
  if (!canPlay(col)) {
    return;
  }
  mask |= mask + bottomMask(col);
}

/*
 * Store the board of the current player in current board
 */
void Bitboard::updateBoard() {
  currentBoard ^= mask;  // bitwise xor
}

/*
 * returns true unless mask has an equivalent bit to topmask, i.e. when column
 * is full.
 */
bool Bitboard::canPlay(int col) const { return (mask & topMask(col)) == 0; }

uint64_t Bitboard::convertToBitboard(const Board& board,
                                     Disc::Colour currentPlayer) {
  uint64_t bitboardCounter{1};
  uint64_t counter{0};
  int colCounter{0};
  currentBoard = 0;
  mask = 0;
  for (const auto& col : board.getColumns()) {
    for (int i = 0; i < nRows; ++i) {
      if (static_cast<Disc::Colour>(col.getSquareStatus(i)) == currentPlayer) {
        currentBoard += bitboardCounter;
      }
      // store all occupied positions in mask
      if (col.getSquareStatus(i) != Column::SquareStatus::empty) {
        mask += bitboardCounter;
      }
      bitboardCounter = UINT64_C(1) << ++counter;
    }
    // skip next row because it can't hold any discs, just marks when column
    // is full.
    bitboardCounter = UINT64_C(1) << ++counter;
  }
}

bool Bitboard::isWinningMove(int col) const {
  uint64_t tempBoard = currentBoard;
  tempBoard |= (mask + bottomMask(col)) & columnMask(col);
  return checkWin(tempBoard);
}

bool Bitboard::checkWin(uint64_t board) const {
  // To check wins, perform 3 shifts.
  // After each shift, the bits should still be aligned if there is a win.
  // Alignment is checked using bitwise '&' operator which will be non-zero
  // if there are matching bits after shifting.

  // horizontal
  uint64_t align = board & (board >> nRows + 1);  // shift by one column
  align = align & (align << 2 * (nRows + 1));     // shift by two more columns
  if (align) return true;

  // diagonal 1
  align = board & (board >> nRows);
  align = align & (align >> 2 * nRows);
  if (align) return true;

  // diagonal 2
  align = board & (board >> nRows + 2);
  align = align & (align >> 2 * (nRows + 2));
  if (align) return true;

  // vertical
  align = board & (board >> 1);
  align = align & (align >> 2);
  if (align) return true;
}

uint64_t Bitboard::createKey() const {
  return currentBoard + mask;  // creates a unique key because current board
                               // contains either 1's or 0's depending on the
                               // current player, but mask will be the same for
                               // that board state regardless of current player.
}

void Bitboard::reset() {
  currentBoard = 0;
  mask = 0;
}

uint64_t Bitboard::getCurrentBoard() const { return currentBoard; }

uint64_t Bitboard::getMask() const { return mask; }

uint64_t Bitboard::topMask(int col) const {
  return UINT64_C(1) << (nRows - 1) << col * (nRows + 1);
}

uint64_t Bitboard::bottomMask(int col) const {
  return UINT64_C(1) << col * (nRows + 1);
}

uint64_t Bitboard::columnMask(int col) const {
  // shift to last bit in column (e.g. 2^6 = 64)
  // then -1 to turn all bits before nRow'th bit and mark an entire column:
  // e.g. 64-1 = 63 = 2^0+2^1+2^2+2^3+2^4+2^5 marks elements 0,1,2,3,4,5
  // then shift these bits to chosen column
  return ((UINT64_C(1) << nRows) - 1) << col * (nRows + 1);
}
