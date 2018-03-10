#include "TranspositionTable.h"

#include <gsl/gsl>

TranspositionTable::TranspositionTable(unsigned int size) : table(size) {
  Expects(size > 0);
}

void TranspositionTable::reset() {
  std::fill(table.begin(), table.end(), Entry{0, 0});
}

void TranspositionTable::put(uint64_t key, uint8_t val) {
  Expects(key < (INT64_C(1) << 56));
  unsigned int i = index(key);
  table[i].key = key;
  table[i].val = val;
}

uint8_t TranspositionTable::get(uint64_t key) const {
  Expects(key < (INT64_C(1) << 56));
  unsigned int i = index(key);
  if (table[i].key == key) {
    return table[i].val;
  } else {
    return 0;
  }
}
unsigned int TranspositionTable::index(uint64_t key) const {
  return key % table.size();
}
