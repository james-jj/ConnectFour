#include "Bitboard.h"
#include "TranspositionTable.h"

#include "catch.hpp"

TEST_CASE("Bitboard can be stored and retrieved") {
  TranspositionTable table(2);
  Bitboard bitboard;

  bitboard.addDisc(0);
  bitboard.addDisc(0);
  bitboard.addDisc(0);
  bitboard.addDisc(0);

  table.put(bitboard.createKey(), 1);
  REQUIRE(table.get(bitboard.createKey()) == 1);
  bitboard.addDisc(0);
  REQUIRE(table.get(bitboard.createKey()) == 0);
}
