#ifndef Board_hpp
#define Board_hpp

#include "Column.h"
#include "Disc.h"

#include <stdio.h>
#include <tuple>
#include <vector>

#include <QObject>

/**
 * The Board holds the current board state, e.g.,
 * where discs are placed on the board and the size of the
 * board.
 *
 * A disc can be placed in any column in the board as long
 * as that column isn't full.
 *
 * Board also contains methods to determine whether a
 * connect four has occured relative to the location of the
 * last disc placed in the board.
 */
class Board : public QObject {
  Q_OBJECT
 public:
  Board();
  Board(int _nCols, int _nRows);

  void reset();

  /**
   * @brief addDisc adds disc to the board, discs can't be added to full columns
   * @param discColour
   * @param columnID: 0 based column index
   */
  void addDisc(const Disc::Colour& discColour, int columnID);

  /**
   * @brief hasWin checks for win based on last disc added to the board
   * @return true if there's a win
   */
  bool hasWin();  // check for win based on last disc played

  int getNSquaresRemaining(int columnID) const;
  int getNColumns() const;
  int getNRows() const;
  Disc::Colour getDiscColour(int colID, int rowID) const;
  std::vector<Column> getColumns() const;
  std::tuple<int, int> getLastDiscLoc() const;
  std::vector<std::tuple<int, int>> getWinCoords() const;

 signals:
  void discAddedSignal(int colID, int rowID, Disc::Colour discColour);

 private:
  enum Coordinate { column = 0, row };
  const int nColumns;
  const int nRows;
  std::vector<Column> columns;
  std::vector<int> nSquaresRemaining;
  std::tuple<int, int> lastDiscLocation{-1, -1};
  Disc::Colour lastDiscColour{Disc::Colour::white};
  std::vector<std::tuple<int, int>> winCoords;

  void storeLastDiscInfo(int colID, int rowID, Disc::Colour discColour);
  void initColumns();

  bool columnHasWin(const std::tuple<int, int>& coords,
                    const std::vector<Column>& cols);

  bool rowHasWin(const std::tuple<int, int>& coords,
                 const std::vector<Column>& cols);

  bool diagHasWin(const std::tuple<int, int>& coords,
                  const std::vector<Column>& cols);
};

#endif /* Board_hpp */
