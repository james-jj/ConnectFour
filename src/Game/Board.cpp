//
//  Board.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include "Board.h"

#include <tuple>
#include <vector>

#include <gsl/gsl>

#include "AIController.h"
#include "Column.h"
#include "Disc.h"

Board::Board()
    : nColumns(7), nRows(6), nSquaresRemaining(std::vector<int>(7, 6)) {
  for (auto colID = 0; colID < nColumns; ++colID) {
    columns.push_back(Column(nRows, colID));
  }
}

Board::Board(int _nCols, int _nRows)
    : nColumns(_nCols),
      nRows(_nRows),
      nSquaresRemaining(std::vector<int>(_nCols, _nRows)) {
  Expects(nColumns > 0 && nRows > 0);
  initColumns();
}

void Board::reset() {
  nSquaresRemaining = std::vector<int>(nColumns, nRows);
  columns.clear();
  initColumns();
  lastDiscLocation = {-1, -1};
}

/*
 * addDisc will only add a disc if the column isn't full
 */
void Board::addDisc(const Disc::Colour& discColour, int columnID) {
  Expects(columnID < nColumns && columnID >= 0);
  if (columns[columnID].getIsFull() == false) {
    columns[columnID].addDisc(discColour);
    nSquaresRemaining[columnID]--;
    storeLastDiscInfo(columnID, columns[columnID].getCurrentHeight() - 1,
                      discColour);
  }
  Ensures(nSquaresRemaining[columnID] >= 0);
}

int Board::getNSquaresRemaining(int columnID) const {
  return nSquaresRemaining[columnID];
}

int Board::getNColumns() const { return nColumns; }

std::vector<Column> Board::getColumns() const { return columns; }

int Board::getNRows() const { return nRows; }

void Board::storeLastDiscInfo(int colID, int rowID, Disc::Colour discColour) {
  lastDiscLocation = {colID, rowID};
  lastDiscColour = discColour;
  emit discAddedSignal(colID, rowID, discColour);
}

std::tuple<int, int> Board::getLastDiscLoc() const { return lastDiscLocation; }

Disc::Colour Board::getDiscColour(int colID, int rowID) const {
  return static_cast<Disc::Colour>(columns[colID].getSquareStatus(rowID));
}

bool Board::hasWin() {
  return columnHasWin(lastDiscLocation, columns) ||
         rowHasWin(lastDiscLocation, columns) ||
         diagHasWin(lastDiscLocation, columns);
}

bool Board::columnHasWin(const std::tuple<int, int>& coords,
                         const std::vector<Column>& cols) {
  auto colID{std::get<Coordinate::column>(coords)};
  auto rowID{std::get<Coordinate::row>(coords)};
  // check column only if height > 4, otherwise connect 4 not possible
  if (cols[colID].getCurrentHeight() >= 4) {
    auto discColour{cols[colID].getSquareStatus(rowID)};
    // now check downwards to the bottom of the column for connect four:
    int rowIt{rowID};
    int discCounter{0};
    std::vector<std::tuple<int, int>> winRecord;
    while (discColour == cols[colID].getSquareStatus(rowIt) && rowIt >= 0) {
      winRecord.push_back({colID, rowIt});
      ++discCounter;
      --rowIt;
      if (discCounter == 4) {
        winCoords = winRecord;
        return true;
      }
    }
  }
  return false;
}

bool Board::rowHasWin(const std::tuple<int, int>& coords,
                      const std::vector<Column>& cols) {
  auto colID{std::get<Coordinate::column>(coords)};
  auto rowID{std::get<Coordinate::row>(coords)};
  auto discColour{cols[colID].getSquareStatus(rowID)};
  // check squares in the row to the right of last placed disc
  auto colIt{colID};
  auto discCounter{0};
  auto nColumns{cols.size()};
  std::vector<std::tuple<int, int>> winRecord(4);
  while (colIt < nColumns && discColour == cols[colIt].getSquareStatus(rowID)) {
    ++discCounter;
    winRecord[colIt] = {colIt, rowID};
    ++colIt;
    if (discCounter == 4) {
      winCoords = winRecord;
      return true;
    }
  }
  // check squares in the row to the left of last placed disc
  colIt = colID;
  discCounter = 0;
  winRecord.clear();
  while (colIt >= 0 && discColour == cols[colIt].getSquareStatus(rowID)) {
    winRecord.push_back({colIt, rowID});
    --colIt;
    ++discCounter;
    if (discCounter == 4) {
      winCoords = winRecord;
      return true;
    }
  }
  return false;
}

bool Board::diagHasWin(const std::tuple<int, int>& coords,
                       const std::vector<Column>& cols) {
  auto colID{std::get<Coordinate::column>(coords)};
  auto rowID{std::get<Coordinate::row>(coords)};
  auto discColour{cols[colID].getSquareStatus(rowID)};
  auto colIt{colID};
  auto rowIt{rowID};
  auto discCounter{0};
  // check up and right diagonal
  auto nColumns{cols.size()};
  auto nRows{cols[0].getNSquares()};
  std::vector<std::tuple<int, int>> winRecord;
  while (colIt < nColumns && rowIt < nRows) {
    if (cols[colIt].getSquareStatus(rowIt) == discColour) {
      winRecord.push_back({colIt, rowIt});
      ++discCounter;
      if (discCounter == 4) {
        winCoords = winRecord;
        return true;
      }
      ++colIt;
      ++rowIt;
    } else {
      break;
    }
  }
  // check left and down diagonal
  colIt = colID;
  rowIt = rowID;
  --discCounter;  // decrement so that first disc isn't counted twice
  winRecord.clear();
  while (colIt >= 0 && rowIt >= 0) {
    if (cols[colIt].getSquareStatus(rowIt) == discColour) {
      winRecord.push_back({colIt, rowIt});
      ++discCounter;
      if (discCounter == 4) {
        winCoords = winRecord;
        return true;
      }
      --colIt;
      --rowIt;
    } else {
      break;
    }
  }
  // check up and left diagonal
  colIt = colID;
  rowIt = rowID;
  discCounter = 0;
  winRecord.clear();
  while (colIt >= 0 && rowIt < nRows) {
    if (cols[colIt].getSquareStatus(rowIt) == discColour) {
      winRecord.push_back({colIt, rowIt});
      ++discCounter;
      if (discCounter == 4) {
        winCoords = winRecord;
        return true;
      }
      --colIt;
      ++rowIt;
    } else {
      break;
    }
  }
  // check down and right diagonal
  colIt = colID;
  rowIt = rowID;
  --discCounter;  // decrement so that first disc isn't counted twice
  winRecord.clear();
  while (colIt < nColumns && rowIt >= 0) {
    if (cols[colIt].getSquareStatus(rowIt) == discColour) {
      winRecord.push_back({colIt, rowIt});
      discCounter++;
      if (discCounter == 4) {
        winCoords = winRecord;
        return true;
      }
      ++colIt;
      --rowIt;
    } else {
      break;
    }
  }
  return false;
}

std::vector<std::tuple<int, int>> Board::getWinCoords() const {
  return winCoords;
}

void Board::initColumns() {
  for (auto i = 0; i < nColumns; ++i) {
    columns.push_back(Column(nRows, i));
  }
}
