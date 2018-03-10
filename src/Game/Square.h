#ifndef Square_hpp
#define Square_hpp

#include "Disc.h"

#include <tuple>

class Square {
 public:
  Square(std::tuple<int, int> _position);

  enum Status { empty = 0, containsWhite, containsBlack };

  void addDisc(const Disc::Colour& discColour);

  std::tuple<int, int> getPosition() const;
  Status getSquareStatus() const;

 private:
  Status status{empty};
  const std::tuple<int, int> position{0, 0};
};

#endif /* Square_hpp */
