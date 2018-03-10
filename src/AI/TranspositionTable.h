#ifndef TRANSPOSITIONTABLE_H
#define TRANSPOSITIONTABLE_H

#include <vector>

#include <stdint.h>

/**
 * @brief The TranspositionTable class is a hashmap with fixed storage size.
 * On collision - previous entry is overriden with new entry.
 *
 * The table is used to cache the most recently visited positions, improving the
 * efficiency of the AI controller's game solver using dynamic programming.
 *
 * Only the most recently visited positions are stored because these positions
 * are more likely to be revisited when exploring nearby positions.
 */
class TranspositionTable {
 public:
  TranspositionTable(unsigned int size);

  void reset();

  void put(uint64_t key, uint8_t val);

  uint8_t get(uint64_t key) const;

 private:
  struct Entry {
    uint64_t key : 56;  // 56 bit keys
    uint8_t val;        // 8 bit values
  };                    // size of entry = 8 bytes

  std::vector<Entry> table;

  unsigned int index(uint64_t key) const;
};

#endif  // TRANSPOSITIONTABLE_H
