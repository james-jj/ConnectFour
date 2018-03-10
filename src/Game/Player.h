#ifndef Player_hpp
#define Player_hpp

#include "Disc.h"

#include <stdio.h>

/**
 * Player contains the player states, e.g. player's disc colour, ID and how many
 * discs are left.
 */
class Player {
 public:
  Player();
  Player(Disc::Colour _colour, int _playerID);

  void restart();

  /**
   * @brief removeDisc removes 1 disc from the player
   */
  void removeDisc();

  Disc::Colour getDiscColour() const;
  bool getIsFirst() const;
  int getNDiscs() const;
  int getPlayerID() const;

  void setNDiscs(int _nDiscs);
  void setDiscColour(const Disc::Colour& newColour);

 private:
  Disc::Colour colour;
  int playerID;
  bool isFirst;
  int nDiscs{21};
};

#endif /* Player_hpp */
