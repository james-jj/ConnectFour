//
//  Game.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include "Game.h"

#include <iostream>
#include <tuple>

#include <QDebug>
#include <QSharedPointer>
#include <QThread>

#include "Board.h"
#include "Disc.h"
#include "Player.h"

// game needs to check whether column is full before letting player add to
// column  if column is full then player must choose another column
Game::Game()
    : players{{Player{Disc::Colour::white, 1}},
              {Player{Disc::Colour::black, 2}}} {
  setFirstPlayer();
  players[1].isAI = true;
}

void Game::setFirstPlayer() {
  players[0].player.getIsFirst() ? currentPlayerIdx = 0 : currentPlayerIdx = 1;
  currentPlayerID = currentPlayerIdx + 1;
}

void Game::newGame() {
  for (auto& playerInfo : players) {
    playerInfo.player.restart();
    playerInfo.score = 0;
  }
  initGame();
}

std::vector<unsigned int> Game::getScores() const {
  std::vector<unsigned int> scores;
  for (const auto& playerInfo : players) {
    scores.push_back(playerInfo.score);
  }
  return scores;
}

int Game::getCurrentPlayerID() const { return currentPlayerID; }

Board& Game::getBoard() { return board; }

void Game::restartGame() {
  for (auto& playerInfo : players) {
    playerInfo.player.restart();
  }
  initGame();
}

void Game::initGame() {
  board.reset();
  setFirstPlayer();
  reportCurrentPlayer(currentPlayerID);
  isFirstTurn = true;
  // take ai turn if AI is first
  if (players[currentPlayerIdx].isAI) {
    auto aiCol = ai.calculateNextMove(
        board, difficulty, players[currentPlayerIdx].player.getDiscColour());
    takeTurn(aiCol);
  }
}

void Game::turnController(int selectedColumn) {
  takeTurn(selectedColumn);  // take human turn
  // take AI turn
  if (players[currentPlayerIdx].isAI) {
    auto aiCol = ai.calculateNextMove(
        board, difficulty, players[currentPlayerIdx].player.getDiscColour());
    takeTurn(aiCol);
  }
}

void Game::takeTurn(int selectedColumn) {
  // if move is valid then add a disc to the board and take a disc from the
  // player
  if (isTurnValid(selectedColumn)) {
    board.addDisc(players[currentPlayerIdx].player.getDiscColour(),
                  selectedColumn);
    players[currentPlayerIdx].player.removeDisc();
    if (!isFirstTurn) {
      if (isWon()) {
        players[currentPlayerIdx].score += 1;
        emit reportWinSignal(currentPlayerID, board.getWinCoords());
        return;
      }
    }
    currentPlayerIdx == 0 ? currentPlayerIdx = 1 : currentPlayerIdx = 0;
    currentPlayerID = currentPlayerIdx + 1;
    emit reportCurrentPlayer(currentPlayerID);
    isFirstTurn = false;
  }
  return;
}

bool Game::isTurnValid(int selectedColumn) const {
  bool isValid = false;
  if (isInputInRange(selectedColumn)) {
    if (isSpaceInColumn(selectedColumn)) {
      isValid = true;
    }
  }
  return isValid;
}

bool Game::isWon() { return board.hasWin(); }

bool Game::isSpaceInColumn(int selectedColumn) const {
  if (board.getNSquaresRemaining(selectedColumn) > 0) {
    return true;
  }
  return false;
}

bool Game::isInputInRange(int selectedColumn) const {
  // error check on input:
  if (selectedColumn >= 0 && selectedColumn < board.getNColumns()) {
    return true;
  }
  return false;
}
