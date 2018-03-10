//
//  testBoard.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include <stdio.h>
#include <tuple>
#include "Board.h"
#include "Disc.h"
#include "GUI.h"
#include "catch.hpp"

// test that number of squares remaining in a column is always >= 0
int testNSquaresGEZero() {
  int nCols = 7, nRows = 6;
  Board board(nCols, nRows);
  int columnID = 0;
  for (int i = 0; i < 100; ++i) {
    board.addDisc(Disc::Colour::white, columnID);
  }

  return board.getNSquaresRemaining(columnID);
}

TEST_CASE(
    "Number of squares remaining in a column on the board can't become "
    "negative") {
  REQUIRE(testNSquaresGEZero() >= 0);
}

TEST_CASE(
    "Adding discs to column causes number of squares to decrease until "
    "reaching 0") {
  int nCols = 7, nRows = 6;
  Board board(nCols, nRows);

  int columnID = 0;
  int counter = nRows;

  for (int i = 0; i < nRows; ++i) {
    board.addDisc(Disc::Colour::white, columnID);
    REQUIRE(board.getNSquaresRemaining(columnID) == --counter);
  }
}

TEST_CASE(
    "Correct last disc location is stored when new disc is added to a column") {
  int nCols = 7, nRows = 6;
  Board board(nCols, nRows);

  int columnID = 0;
  int counter = nRows;

  for (int i = 0; i < nRows; ++i) {
    board.addDisc(Disc::Colour::white, columnID);
    REQUIRE(board.getLastDiscLoc() == std::make_tuple(0, i));
  }
}

TEST_CASE("Connect fours are correctly detected as wins") {
  int nCols = 7, nRows = 6;
  Board *board;

  SECTION("Vertical connect fours are detected") {
    board = new Board(nCols, nRows);
    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::white, 0);
    }
    REQUIRE(board->hasWin() == true);
    std::vector<std::tuple<int, int>> ans{{{0, 3}, {0, 2}, {0, 1}, {0, 0}}};
    REQUIRE(board->getWinCoords() == ans);

    delete board;
    board = new Board(nCols, nRows);

    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::white, nCols - 1);
    }
    REQUIRE(board->hasWin() == true);

    delete board;
    board = new Board(nCols, nRows);

    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::black, nCols - 1);
    }
    REQUIRE(board->hasWin() == true);

    delete board;
    board = new Board(nCols, nRows);
    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::black, 0);
    }
    REQUIRE(board->hasWin() == true);

    delete board;
    board = new Board(nCols, nRows);
    board->addDisc(Disc::Colour::white, 0);
    board->addDisc(Disc::Colour::white, 0);
    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::black, 0);
    }
    REQUIRE(board->hasWin() == true);
  }

  SECTION("Horizontal connect fours are detected") {
    board = new Board(nCols, nRows);
    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::white, i);
    }
    REQUIRE(board->hasWin() == true);
    std::vector<std::tuple<int, int>> ans{{{3, 0}, {2, 0}, {1, 0}, {0, 0}}};
    REQUIRE(board->getWinCoords() == ans);

    delete board;
    board = new Board(nCols, nRows);
    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::black, i);
    }
    REQUIRE(board->hasWin() == true);

    delete board;
    board = new Board(nCols, nRows);
    for (int i = 2; i < 6; ++i) {
      board->addDisc(Disc::Colour::white, i);
    }
    REQUIRE(board->hasWin() == true);

    delete board;
    board = new Board(nCols, nRows);
    int whiteBlackCounter = 0;
    for (int i = 0; i < nRows - 1; ++i) {
      for (int j = 0; j < nCols; ++j) {
        whiteBlackCounter++;
        if (whiteBlackCounter % 2 == 0) {
          board->addDisc(Disc::Colour::white, j);
        } else {
          board->addDisc(Disc::Colour::black, j);
        }
      }
    }

    for (int i = 0; i < 4; ++i) {
      board->addDisc(Disc::Colour::black, i);
    }

    REQUIRE(board->hasWin() == true);

    delete board;
    board = new Board(nCols, nRows);

    whiteBlackCounter = 0;
    for (int i = 0; i < nRows - 1; ++i) {
      for (int j = 0; j < nCols; ++j) {
        whiteBlackCounter++;
        if (whiteBlackCounter % 2 == 0) {
          board->addDisc(Disc::Colour::white, j);
        } else {
          board->addDisc(Disc::Colour::black, j);
        }
      }
    }

    for (int i = 3; i < nCols; ++i) {
      board->addDisc(Disc::Colour::black, i);
    }

    REQUIRE(board->hasWin() == true);
    delete board;
  }

  SECTION("Diagonal connect fours are detected") {
    /*
     x x x x x x x
     x x x x x x x
     X x x B x x x
     X X B W x x x
     X B W W x x x
     B W W W x x x
     */

    board = new Board(nCols, nRows);
    board->addDisc(Disc::Colour::black, 0);

    board->addDisc(Disc::Colour::white, 1);
    board->addDisc(Disc::Colour::black, 1);

    board->addDisc(Disc::Colour::white, 2);
    board->addDisc(Disc::Colour::white, 2);
    board->addDisc(Disc::Colour::black, 2);

    board->addDisc(Disc::Colour::white, 3);
    board->addDisc(Disc::Colour::white, 3);
    board->addDisc(Disc::Colour::white, 3);
    board->addDisc(Disc::Colour::black, 3);
    REQUIRE(board->hasWin() == true);
    std::vector<std::tuple<int, int>> ans = {{3, 3}, {2, 2}, {1, 1}, {0, 0}};
    REQUIRE(board->getWinCoords() == ans);

    delete board;
    board = new Board(nCols, nRows);

    /*
    x x x x x x x
    x x x x x x x
    B x x x x x x
    W B x x x x x
    W W B x x x x
    W W W B x x x
     */

    board->addDisc(Disc::Colour::white, 0);
    board->addDisc(Disc::Colour::white, 0);
    board->addDisc(Disc::Colour::white, 0);
    board->addDisc(Disc::Colour::black, 0);

    board->addDisc(Disc::Colour::white, 1);
    board->addDisc(Disc::Colour::white, 1);
    board->addDisc(Disc::Colour::black, 1);

    board->addDisc(Disc::Colour::white, 2);
    board->addDisc(Disc::Colour::black, 2);

    board->addDisc(Disc::Colour::black, 3);

    REQUIRE(board->hasWin() == true);
    ans = {{3, 0}, {2, 1}, {1, 2}, {0, 3}};
    REQUIRE(board->getWinCoords() == ans);

    delete board;
    board = new Board(nCols, nRows);
  }
}
