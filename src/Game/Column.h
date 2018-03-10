#ifndef Column_hpp
#define Column_hpp

#include "Square.h"

#include <stdio.h>
#include <tuple>
#include <vector>

/**
 * Columns are made up of grid squares up to the column height.
 *
 * A disc can be added to a column and the disc will be placed at the next
 * highest empty grid square, to represent a disc being dropped into a column in
 * Connect Four.
 *
 * When a column is full, no more discs can be added to that column.
 */
class Column {
 public:
  enum SquareStatus { empty = 0, containsWhite, containsBlack };

  Column(int _nSquares, int _columnID);

  void addDisc(const Disc::Colour& discColour);

  /**
   * @brief removeDisc removes the last disc added to the column
   */
  void removeDisc();

  bool getIsFull() const;
  int getSquareStatus(int row) const;
  int getCurrentHeight() const;
  int getNSquares() const;

 private:
  struct Square {
    SquareStatus status;
    const int row;
  };
  const int columnID;           // ID of the column relative on the board
  const int columnHeight;       // number of squares in the column
  std::vector<Square> squares;  // each position in the column is a square which
                                // can contain a disc
  int nDiscs{0};                // number of discs in the column
  bool isFull{false};
  int currentHeight{0};

  void setIsFull();
};

#endif /* Column_hpp */
