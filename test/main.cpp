////
////  main.cpp
////  ConnectFourTests
////
////  Created by James Johnstone on 05/08/2017.
////  Copyright © 2017 James Johnstone. All rights reserved.
////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

////#include <iostream>
//#include "Board.h"
//#include "AIController.h"

//int main()
//{
//    auto nCols = 7;
//    auto nRows = 6;
//    Board board(nCols,nRows);
//    AIController ai;

////    SECTION("Columnwise win on next move")
////    {

//    /*
//    x x B B x x x
//    x x W W x x W
//    B W B B W B B
//    W B W W B W W
//    B W B B W B B
//    W B W W B W W
//    */

////    board.addDisc(Disc::Colour::white, 0);
////    board.addDisc(Disc::Colour::black, 0);
////    board.addDisc(Disc::Colour::white, 0);
////    board.addDisc(Disc::Colour::black, 0);

////    board.addDisc(Disc::Colour::black, 1);
////    board.addDisc(Disc::Colour::white, 1);
////    board.addDisc(Disc::Colour::black, 1);
////    board.addDisc(Disc::Colour::white, 1);

////    board.addDisc(Disc::Colour::white, 2);
////    board.addDisc(Disc::Colour::black, 2);
////    board.addDisc(Disc::Colour::white, 2);
////    board.addDisc(Disc::Colour::black, 2);
////    board.addDisc(Disc::Colour::white, 2);
////    board.addDisc(Disc::Colour::black, 2);

////    board.addDisc(Disc::Colour::white, 3);
////    board.addDisc(Disc::Colour::black, 3);
////    board.addDisc(Disc::Colour::white, 3);
////    board.addDisc(Disc::Colour::black, 3);
////    board.addDisc(Disc::Colour::white, 3);
////    board.addDisc(Disc::Colour::black, 3);

////    board.addDisc(Disc::Colour::black, 4);
////    board.addDisc(Disc::Colour::white, 4);
////    board.addDisc(Disc::Colour::black, 4);
////    board.addDisc(Disc::Colour::white, 4);

////    board.addDisc(Disc::Colour::white, 5);
////    board.addDisc(Disc::Colour::black, 5);
////    board.addDisc(Disc::Colour::white, 5);
////    board.addDisc(Disc::Colour::black, 5);

////    board.addDisc(Disc::Colour::white, 6);
////    board.addDisc(Disc::Colour::black, 6);
////    board.addDisc(Disc::Colour::white, 6);
////    board.addDisc(Disc::Colour::black, 6);

////    board.addDisc(Disc::Colour::white, 1);
////    board.addDisc(Disc::Colour::black, 5);
////    board.addDisc(Disc::Colour::black, 6);

//    board.addDisc(Disc::Colour::white, 3);

//    //expected answer for this board format = 3
//    //(taken from http://connect4.gamesolver.org/?pos=17264)
//    auto nMovesRemaining{21};
//    ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::white);
//    //REQUIRE(ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::white) == 4);
//    board.reset();
//}

