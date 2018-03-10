//
//  Column.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include "Column.h"
#include "Disc.h"
#include "Square.h"

#include <gsl/gsl>

#include <tuple>
#include <vector>

Column::Column(int _columnHeight, int _columnID)
    : columnHeight(_columnHeight), columnID(_columnID) {
  // construct all the squares in the column
  for (int rowID = 0; rowID < columnHeight; ++rowID) {
    squares.push_back(Square{SquareStatus::empty, rowID});
  }
}

void Column::addDisc(const Disc::Colour& discColour) {
  if (isFull == false) {
    ++nDiscs;
    ++currentHeight;
    squares[currentHeight - 1].status = static_cast<SquareStatus>(discColour);
    setIsFull();
  }
}

void Column::removeDisc() {
  squares[currentHeight - 1].status = SquareStatus::empty;
  --nDiscs;
  --currentHeight;
  setIsFull();
  Ensures(nDiscs >= 0 && currentHeight >= 0);
}

// Column becomes full when number of discs = column height
void Column::setIsFull() {
  if (nDiscs < columnHeight) {
    isFull = false;
  } else {
    isFull = true;
  }
}

bool Column::getIsFull() const { return isFull; }

int Column::getSquareStatus(int row) const {
  return static_cast<int>(squares[row].status);
}

int Column::getCurrentHeight() const { return currentHeight; }

int Column::getNSquares() const { return squares.size(); }
