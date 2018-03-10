//
//  Player.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include "Player.h"
#include <gsl/gsl>
#include <iostream>

Player::Player() {
  colour = Disc::Colour::white;
  playerID = 1;
  isFirst = true;
}

Player::Player(Disc::Colour _colour, int _playerID)
    : colour(_colour), playerID(_playerID) {
  Expects(playerID == 1 || playerID == 2);
  if (colour == Disc::Colour::white) {
    isFirst = true;
  }
}

void Player::restart() {
  nDiscs = 21;
  colour = Disc::chooseRandDiscColour();
  if (colour == Disc::Colour::white) {
    isFirst = true;
  } else {
    isFirst = false;
  }
}

void Player::setNDiscs(int _nDiscs) {
  Expects(_nDiscs >= 0);
  nDiscs = _nDiscs;
}

void Player::setDiscColour(const Disc::Colour& newColour) {
  colour = newColour;
}

Disc::Colour Player::getDiscColour() const { return colour; }

bool Player::getIsFirst() const { return isFirst; }

int Player::getNDiscs() const { return nDiscs; }

int Player::getPlayerID() const { return playerID; }

void Player::removeDisc() { nDiscs--; }
