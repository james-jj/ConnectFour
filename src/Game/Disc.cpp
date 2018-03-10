//
//  Disc.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include "Disc.h"
#include <random>

// Generate a random number between 1 and 10 and return white/black based on
// value of this number  uniform distribution is used to generate 50% black 50%
// white  when a black colour is returned, the next colour returned is white.
// When black is returned, the  next colour returned is black. After two numbers
// have been returned, a new random number is generated.
namespace Disc {
Colour chooseRandDiscColour() {
  static Colour lastColour;
  static bool isFirstCall = true;
  Colour randomColour;

  // on first call, generate first random colour black or white
  // on second call, return the colour that wasn't generated on first call and
  // reset for next call
  if (isFirstCall) {
    // generate non deterministic random number between 1 and 100
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> uniform_dist(1, 10);

    // disc colour is white if random number between 1 and 5, black if between 6
    // and 10
    uniform_dist(el) > 5 ? randomColour = Colour::white
                         : randomColour = Colour::black;
    lastColour = randomColour;
    isFirstCall = false;
  } else {
    // if last colour was white then new colour is black, if last colour was
    // black then new colour is white
    lastColour == Colour::white ? randomColour = Colour::black
                                : randomColour = Colour::white;
    isFirstCall = true;
  }
  return randomColour;
}
}  // namespace Disc
