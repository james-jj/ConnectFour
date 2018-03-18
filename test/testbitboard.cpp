#include "Bitboard.h"
#include "Board.h"
#include "Disc.h"

#include "catch.hpp"

#include <cmath>
#include <vector>

uint64_t calcPowersOfTwo(const std::vector<double>& exponents) {
  uint64_t total{0};
  for (const auto& exponent : exponents) {
    total += static_cast<uint64_t>(pow(2, exponent));
  }
  return total;
}

TEST_CASE("Board is correctly converted to bitboard") {
  Board board;
  Bitboard bitBoard;

  SECTION("Edge cases") {
    // empty board
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.getCurrentBoard() == UINT64_C(0));
    uint64_t expectedAnswer = UINT64_C(0);
    REQUIRE(bitBoard.getMask() == expectedAnswer);

    // full board
    uint64_t expectedSize{0};
    int power{0};
    for (int i = 0; i < 7; ++i) {
      for (int j = 0; j < 6; ++j) {
        board.addDisc(Disc::Colour::white, i);
        expectedSize += static_cast<uint64_t>(pow(2, power++));
      }
      power++;  // skip the row that just marks when columns are full
    }
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.getCurrentBoard() == expectedSize);
    REQUIRE(bitBoard.getMask() == expectedSize);
  }

  SECTION("Simple tests") {
    board.reset();
    board.addDisc(Disc::Colour::white, 0);

    bitBoard.convertToBitboard(board, Disc::Colour::white);

    REQUIRE(bitBoard.getCurrentBoard() == UINT64_C(1));

    board.addDisc(Disc::Colour::white, 0);
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.getCurrentBoard() == UINT64_C(3));

    board.addDisc(Disc::Colour::black, 0);
    board.addDisc(Disc::Colour::white, 0);
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.getCurrentBoard() == UINT64_C(11));
    uint64_t expectedMask = calcPowersOfTwo({0, 1, 2, 3});
    REQUIRE(bitBoard.getMask() == expectedMask);
  }

  SECTION("Harder tests") {
    board.reset();

    board.addDisc(Disc::Colour::white, 2);
    board.addDisc(Disc::Colour::black, 2);
    board.addDisc(Disc::Colour::white, 2);
    board.addDisc(Disc::Colour::black, 3);
    board.addDisc(Disc::Colour::white, 3);
    board.addDisc(Disc::Colour::black, 3);
    board.addDisc(Disc::Colour::white, 4);
    board.addDisc(Disc::Colour::black, 4);
    board.addDisc(Disc::Colour::white, 4);

    bitBoard.convertToBitboard(board, Disc::Colour::white);
    uint64_t expectedAnswer = calcPowersOfTwo({14, 16, 22, 28, 30});
    uint64_t expectedMask =
        calcPowersOfTwo({14, 15, 16, 21, 22, 23, 28, 29, 30});
    REQUIRE(bitBoard.getCurrentBoard() == expectedAnswer);
    REQUIRE(bitBoard.getMask() == expectedMask);
  }
}

TEST_CASE("canPlay returns false when column is full") {
  Board board;
  Bitboard bitBoard;

  SECTION("Edge cases") {
    // empty board
    bitBoard.convertToBitboard(board, Disc::Colour::black);
    for (int i = 0; i < 7; ++i) {
      REQUIRE(bitBoard.canPlay(i));
    }

    // full board
    for (int i = 0; i < 7; ++i) {
      for (int j = 0; j < 6; ++j) {
        board.addDisc(Disc::Colour::white, i);
      }
    }
    bitBoard.convertToBitboard(board, Disc::Colour::black);
    for (int i = 0; i < 7; ++i) {
      REQUIRE(!bitBoard.canPlay(i));
    }
  }

  board.reset();
  for (int i = 0; i < 7; ++i) {
    board.addDisc(Disc::Colour::white, 0);
  }
  bitBoard.convertToBitboard(board, Disc::Colour::black);

  REQUIRE(!bitBoard.canPlay(0));
  for (int i = 1; i < 7; ++i) {
    REQUIRE(bitBoard.canPlay(i));
  }

  for (int i = 0; i < 7; ++i) {
    board.addDisc(Disc::Colour::white, 6);
  }

  bitBoard.convertToBitboard(board, Disc::Colour::black);
  REQUIRE(!bitBoard.canPlay(0));
}

TEST_CASE("Check win detects wins") {
  Board board;
  Bitboard bitBoard;
  int nCols{7};
  int nRows{6};

  SECTION("Vertical wins") {
    for (int i = 0; i < 4; ++i) {
      board.addDisc(Disc::Colour::white, nCols - 1);
    }
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
    board.reset();

    for (int i = 0; i < 4; ++i) {
      board.addDisc(Disc::Colour::black, nCols - 1);
    }
    bitBoard.convertToBitboard(board, Disc::Colour::black);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
    board.reset();

    board.addDisc(Disc::Colour::white, 0);
    board.addDisc(Disc::Colour::white, 0);
    for (int i = 0; i < 4; ++i) {
      board.addDisc(Disc::Colour::black, 0);
    }
    bitBoard.convertToBitboard(board, Disc::Colour::black);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
  }

  SECTION("Horizontal wins") {
    board.reset();
    for (int i = 0; i < 4; ++i) {
      board.addDisc(Disc::Colour::white, i);
    }
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
    board.reset();

    for (int i = 2; i < 6; ++i) {
      board.addDisc(Disc::Colour::white, i);
    }
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
    board.reset();

    int whiteBlackCounter{0};
    for (int i = 0; i < nRows - 1; ++i) {
      for (int j = 0; j < nCols; ++j) {
        whiteBlackCounter++;
        if (whiteBlackCounter % 2 == 0) {
          board.addDisc(Disc::Colour::white, j);
        } else {
          board.addDisc(Disc::Colour::black, j);
        }
      }
    }

    for (int i = 0; i < 4; ++i) {
      board.addDisc(Disc::Colour::black, i);
    }
    bitBoard.convertToBitboard(board, Disc::Colour::black);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
    board.reset();

    whiteBlackCounter = 0;
    for (int i = 0; i < nRows - 1; ++i) {
      for (int j = 0; j < nCols; ++j) {
        whiteBlackCounter++;
        if (whiteBlackCounter % 2 == 0) {
          board.addDisc(Disc::Colour::white, j);
        } else {
          board.addDisc(Disc::Colour::black, j);
        }
      }
    }

    for (int i = 3; i < nCols; ++i) {
      board.addDisc(Disc::Colour::black, i);
    }

    bitBoard.convertToBitboard(board, Disc::Colour::black);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
  }

  SECTION("Diagonal wins") {
    /*
         x x x x x x x
         x x x x x x x
         X x x B x x x
         X X B W x x x
         X B W W x x x
         B W W W x x x
         */

    board.reset();
    board.addDisc(Disc::Colour::black, 0);

    board.addDisc(Disc::Colour::white, 1);
    board.addDisc(Disc::Colour::black, 1);

    board.addDisc(Disc::Colour::white, 2);
    board.addDisc(Disc::Colour::white, 2);
    board.addDisc(Disc::Colour::black, 2);

    board.addDisc(Disc::Colour::white, 3);
    board.addDisc(Disc::Colour::white, 3);
    board.addDisc(Disc::Colour::white, 3);
    board.addDisc(Disc::Colour::black, 3);
    bitBoard.convertToBitboard(board, Disc::Colour::black);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));
    board.reset();

    /*
        x x x x x x x
        x x x x x x x
        B x x x x x x
        W B x x x x x
        W W B x x x x
        W W W B x x x
         */

    board.addDisc(Disc::Colour::white, 0);
    board.addDisc(Disc::Colour::white, 0);
    board.addDisc(Disc::Colour::white, 0);
    board.addDisc(Disc::Colour::black, 0);

    board.addDisc(Disc::Colour::white, 1);
    board.addDisc(Disc::Colour::white, 1);
    board.addDisc(Disc::Colour::black, 1);

    board.addDisc(Disc::Colour::white, 2);
    board.addDisc(Disc::Colour::black, 2);

    board.addDisc(Disc::Colour::black, 3);

    bitBoard.convertToBitboard(board, Disc::Colour::black);
    REQUIRE(bitBoard.checkWin(bitBoard.getCurrentBoard()));

    board.reset();
    board.addDisc(Disc::Colour::white, 4);
    board.addDisc(Disc::Colour::white, 4);
    board.addDisc(Disc::Colour::white, 4);
    board.addDisc(Disc::Colour::white, 3);
    bitBoard.convertToBitboard(board, Disc::Colour::white);
    REQUIRE(!bitBoard.checkWin(bitBoard.getCurrentBoard()));
  }
}

TEST_CASE("Discs can be added to columns") {
  Bitboard bitBoard;

  bitBoard.addDisc(0);
  REQUIRE(bitBoard.getMask() == UINT64_C(1));

  bitBoard.addDisc(0);
  REQUIRE(bitBoard.getMask() == UINT64_C(3));

  bitBoard.addDisc(6);
  bitBoard.addDisc(6);
  REQUIRE(bitBoard.getMask() == UINT64_C(13194139533315));

  bitBoard.updateBoard();
  REQUIRE(bitBoard.getCurrentBoard() == UINT64_C(13194139533315));

  bitBoard.addDisc(0);
  bitBoard.addDisc(0);
  bitBoard.addDisc(0);
  bitBoard.addDisc(0);
  REQUIRE(bitBoard.getMask() == UINT64_C(13194139533375));
  bitBoard.updateBoard();
  REQUIRE(bitBoard.getCurrentBoard() == UINT64_C(60));
}

TEST_CASE("isWinningMove returns true when next move is a win") {
  Bitboard bitboard;
  for (int i = 0; i < 3; i++) {
    bitboard.addDisc(0);
  }
  bitboard.updateBoard();
  REQUIRE(bitboard.isWinningMove(0));

  bitboard.reset();
  for (int i = 0; i < 3; i++) {
    bitboard.addDisc(1);
  }
  bitboard.updateBoard();
  REQUIRE(!bitboard.isWinningMove(0));
  REQUIRE(bitboard.isWinningMove(1));
}

TEST_CASE("Win is detected after adding discs to columns") {
  SECTION("Simple column win test using update board") {
    Bitboard bitboard;
    for (int i = 0; i < 4; i++) {
      bitboard.addDisc(0);
    }
    bitboard.updateBoard();
    REQUIRE(bitboard.checkWin(bitboard.getCurrentBoard()));
  }

  SECTION("Simple column win test using takeTurn") {
    Bitboard bitboard;
    bitboard.takeTurn(0);
    bitboard.takeTurn(1);
    bitboard.takeTurn(0);
    bitboard.takeTurn(1);
    bitboard.takeTurn(0);
    bitboard.takeTurn(1);
    REQUIRE(bitboard.isWinningMove(0));
    bitboard.takeTurn(0);
    bitboard.updateBoard();
    REQUIRE(bitboard.checkWin(bitboard.getCurrentBoard()));
  }
}
