#ifndef BITBOARD_H
#define BITBOARD_H

#include "Board.h"
#include "Disc.h"

/**
 * @brief The bitboard class represents the connect four board using bits, in
 * order to improve the efficiency of the AI controller game solver.
 *
 * A board of size H*W needs W*(H+1) bits. So the default board size: 49bits.
 * This is because an additional row is needed at the top of the board in order
 * to create a unique key for a unique board state.
 *
 * Example:
 *
 * Each element below corresponds to the bit position in a bitset.
 *
 * Additional row elements to create unique key:
 * 6 13 20 27 34 41 48
 *
 * Board elements:
 * 5 12 19 26 33 40 47
 * 4 11 18 25 32 39 46
 * 3 10 17 24 31 38 45   ^
 * 2  9 16 23 30 37 44   |
 * 1  8 15 22 29 36 43   |
 * 0  7 14 21 28 35 42  rows
 * columns --->
 *
 * Two separate bitmaps are combined to store a board - one containing the
 * current player's positions and another identifying all occupied positions.
 *
 * Board:         current player    occupied positions
 *                bitmap:           bitmap:
 *                0 0 0 0 0 0 0     0 0 0 0 0 0 0
 * . . . . . . .  0 0 0 0 0 0 0     0 0 0 0 0 0 0
 * . . . . . . .  0 0 0 0 0 0 0     0 0 0 0 0 0 0
 * . . . . . . .  0 0 0 0 0 0 0     0 0 0 0 0 0 0
 * . . . . . . .  0 0 0 0 0 0 0     0 0 0 0 0 0 0
 * . . . . . . .  0 0 0 0 0 0 0     0 0 0 0 0 0 0
 * . . o x x o .  0 0 0 1 1 0 0     0 0 1 1 1 1 0
 *
 * In order to create a unique key for each board state (for fast
 * TranspositionTable look ups), the current payer bitmap and occupied positions
 * bitmaps are combined, with one added to each column:
 *
 * unique key = current player bitmap + occupied positions bitmap + 1 to each
 * col
 *
 * 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0
 * 0 0 0 1 1 0 0
 * 1 1 1 1 1 1 1
 *
 */
class Bitboard {
 public:
  Bitboard() = default;
  Bitboard(int nCols, int nRows);

  /**
   * @brief takeTurn adds a disc to selected column and switches to opposing
   * player for next call to takeTurn.
   * @param col: 0 based index of column
   */
  void takeTurn(int col);

  /**
   * @brief reverseTurn reverses the actions performed in takeTurn
   * @param col: 0 based index of column
   */
  void reverseTurn(int col);

  /**
   * @brief canPlay determines whether column is playable
   * @param col: 0 based index of column
   * @return true if column is playable
   */
  bool canPlay(int col) const;

  /**
   * @brief checkWin checks for horizontal, vertical & diagonal wins for player
   * with 1's in bitboard.
   * @param board: bitboard containing current board state
   * @return true for a win
   */
  bool checkWin(uint64_t board) const;

  /**
   * @brief isWinningMove check whether the next move in a column will be a
   * winning move but doesn't actually play a disc.
   * @param col: 0 based index of column
   * @return true for a win
   */
  bool isWinningMove(int col) const;

  /**
   * @brief convertToBitboard converts the board state stored by a Board object
   * to a bitboard.
   * @param board: current board state.
   * @param currentPlayer
   * @return bitboard representation of board
   */
  uint64_t convertToBitboard(const Board& board, Disc::Colour currentPlayer);

  /**
   * @brief createKey creates a unique key of the current board state
   * @return unique key of the current board state
   */
  uint64_t createKey() const;

  /**
   * @brief addDisc adds disc in the selected column if selection is valid
   * but doesn't switch to opposing player. This is used for testing so that
   * multiple discs of the same colour can be added in a row.
   * @param col: 0 based index of column
   */
  void addDisc(int col);

  /**
   * @brief updateBoard modifies the current board to represent discs added
   * by current player, and switches to opposing player. This is used in
   * conjunction with addDisc in testing.
   */
  void updateBoard();

  void reset();

  uint64_t getCurrentBoard() const;
  uint64_t getMask() const;

 private:
  const int nCols{7};
  const int nRows{6};
  const int bitboardRows{7};  // additional row needed to create unique key
  uint64_t mask{0};  // contains all occupied positions (current and opposing)
  uint64_t currentBoard{0};  // contains current player's occupied positions
  uint64_t nTurns{0};

  /**
   * @brief topMask determines the location of the top of a column given
   * the board dimensions.
   * Example: for a 7x6 board, input col = 6 returns:
   * 2^47, ie. element 47 in a 49 element bit board (indexed from 0)
   * @param col: 0 based index of column
   * @return bitmask containing a 1 marking the location of the top of a column
   */
  uint64_t topMask(int col) const;

  /**
   * @brief bottomMask determines location of the bottom of a column given
   * the board dimensions.
   * Example: for a 7x6 board, input col = 6 returns:
   * 2^42, i.e. element 42 in a 49 element bit board (indexed from zero)
   * @param col: 0 based index of column
   * @return bitmask containing a 1 marking the location of the bottom of a
   * column
   */
  uint64_t bottomMask(int col) const;

  /**
   * @brief columnMask determines location of all elements in a column
   * @param col: 0 based index of column
   * @return bitmask containing a 1 for each element in a column
   */
  uint64_t columnMask(int col) const;
};

#endif  // BITBOARD_H
