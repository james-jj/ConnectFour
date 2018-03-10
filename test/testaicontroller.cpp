#include "AIController.h"
#include "Board.h"

#include "catch.hpp"

void populateColumn(Board &board, int column)
{
    for(auto i = 0; i < 3; ++i)
    {
        board.addDisc(Disc::Colour::white, column);
    }
}

void populateRow(Board &board, Disc::Colour colour, std::tuple<int,int> startEndRow)
{
    for(auto i = std::get<0>(startEndRow); i < std::get<1>(startEndRow)+1; ++i)
    {
        board.addDisc(colour, i);
    }
}

TEST_CASE("AIController chooses correct column when next move is a win")
{
    auto nCols = 7;
    auto nRows = 6;
    Board board(nCols,nRows);
    AIController ai;

    SECTION("Columnwise win on next move")
    {
        populateColumn(board,0);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 0);
        board.reset();

        populateColumn(board,1);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 1);
        board.reset();

        populateColumn(board,2);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 2);
        board.reset();

        populateColumn(board,3);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 3);
        board.reset();

        populateColumn(board,4);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 4);
        board.reset();

        populateColumn(board,5);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 5);
        board.reset();

        populateColumn(board,6);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 6);
        board.reset();
    }

    SECTION("Row-wise win on next move")
    {

        populateRow(board, Disc::Colour::white, {0,2});
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 3);
        board.reset();

        populateRow(board, Disc::Colour::black, {0,0});
        populateRow(board, Disc::Colour::white, {1,3});
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 4);
        board.reset();

        populateRow(board, Disc::Colour::black, {0,1});
        populateRow(board, Disc::Colour::white, {2,4});
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 5);
        board.reset();

        populateRow(board, Disc::Colour::black, {0,2});
        populateRow(board, Disc::Colour::white, {3,5});
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::white) == 6);
        board.reset();
    }

    SECTION("Diagonal win on next move")
    {
        /*
         x x x x x x x
         x x x x x x x
         X x x B x x x
         X X B W x x x
         X B W W x x x
         B W W W x x x
         */
        board.addDisc(Disc::Colour::black, 0);

        board.addDisc(Disc::Colour::white, 1);
        board.addDisc(Disc::Colour::black, 1);

        board.addDisc(Disc::Colour::white, 2);
        board.addDisc(Disc::Colour::white, 2);
        board.addDisc(Disc::Colour::black, 2);

        board.addDisc(Disc::Colour::white, 3);
        board.addDisc(Disc::Colour::white, 3);
        board.addDisc(Disc::Colour::white, 3);
        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::black) == 3);

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

        REQUIRE(ai.calculateNextMove(board, 1, Disc::Colour::black) == 3);
        board.reset();
    }


}

TEST_CASE("AI Controller blocks connect fours"){
    auto nCols{7};
    auto nRows{6};
    Board board(nCols, nRows);
    AIController ai;

    board.addDisc(Disc::Colour::white,3);
    board.addDisc(Disc::Colour::white,3);
    board.addDisc(Disc::Colour::white,3);
    board.addDisc(Disc::Colour::black,5);
    board.addDisc(Disc::Colour::black,2);
//    board.addDisc(Disc::Colour::black,6);

    auto nMovesRemaining{4};
    REQUIRE(ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::black)
            == 3);

    board.reset();
    board.addDisc(Disc::Colour::white,6);
    board.addDisc(Disc::Colour::white,6);
    board.addDisc(Disc::Colour::white,6);
    board.addDisc(Disc::Colour::black,3);
    board.addDisc(Disc::Colour::black,3);
    board.addDisc(Disc::Colour::black,3);
    board.addDisc(Disc::Colour::white,3);

    nMovesRemaining = 4;
    REQUIRE(ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::black)
            == 6);

    board.reset();
    board.addDisc(Disc::Colour::white,3);
    board.addDisc(Disc::Colour::white,4);
    board.addDisc(Disc::Colour::white,5);
    board.addDisc(Disc::Colour::black,2);
    board.addDisc(Disc::Colour::black,3);
    board.addDisc(Disc::Colour::black,3);

    nMovesRemaining = 4;
    REQUIRE(ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::black)
            == 6);

}

TEST_CASE("AI Controller chooses correct column when move after next move is a win")
{
    auto nCols = 7;
    auto nRows = 6;
    Board board(nCols,nRows);
    AIController ai;

    //    SECTION("Columnwise win on next move")
    //    {

    /*
    x x B B x x x
    x x W W x x W
    B W B B W B B
    W B W W B W W
    B W B B W B B
    W B W W B W W
    */

    //    board.addDisc(Disc::Colour::white, 0);
    //    board.addDisc(Disc::Colour::black, 0);
    //    board.addDisc(Disc::Colour::white, 0);
    //    board.addDisc(Disc::Colour::black, 0);

    //    board.addDisc(Disc::Colour::black, 1);
    //    board.addDisc(Disc::Colour::white, 1);
    //    board.addDisc(Disc::Colour::black, 1);
    //    board.addDisc(Disc::Colour::white, 1);

    //    board.addDisc(Disc::Colour::white, 2);
    //    board.addDisc(Disc::Colour::black, 2);
    //    board.addDisc(Disc::Colour::white, 2);
    //    board.addDisc(Disc::Colour::black, 2);
    //    board.addDisc(Disc::Colour::white, 2);
    //    board.addDisc(Disc::Colour::black, 2);

    //    board.addDisc(Disc::Colour::white, 3);
    //    board.addDisc(Disc::Colour::black, 3);
    //    board.addDisc(Disc::Colour::white, 3);
    //    board.addDisc(Disc::Colour::black, 3);
    //    board.addDisc(Disc::Colour::white, 3);
    //    board.addDisc(Disc::Colour::black, 3);

    //    board.addDisc(Disc::Colour::black, 4);
    //    board.addDisc(Disc::Colour::white, 4);
    //    board.addDisc(Disc::Colour::black, 4);
    //    board.addDisc(Disc::Colour::white, 4);

    //    board.addDisc(Disc::Colour::white, 5);
    //    board.addDisc(Disc::Colour::black, 5);
    //    board.addDisc(Disc::Colour::white, 5);
    //    board.addDisc(Disc::Colour::black, 5);

    //    board.addDisc(Disc::Colour::white, 6);
    //    board.addDisc(Disc::Colour::black, 6);
    //    board.addDisc(Disc::Colour::white, 6);
    //    board.addDisc(Disc::Colour::black, 6);

    //    board.addDisc(Disc::Colour::white, 1);
    //    board.addDisc(Disc::Colour::black, 5);
    //    board.addDisc(Disc::Colour::black, 6);

    //    board.addDisc(Disc::Colour::white, 0);
    //    board.addDisc(Disc::Colour::black, 0);
    //    board.addDisc(Disc::Colour::white, 0);
    //    board.addDisc(Disc::Colour::black, 0);
    //    board.addDisc(Disc::Colour::white, 0);
    //board.addDisc(Disc::Colour::black, 3);
    //board.addDisc(Disc::Colour::black, 3);
    //board.addDisc(Disc::Colour::black, 3);

    board.addDisc(Disc::Colour::white, 0);
    board.addDisc(Disc::Colour::black, 1);
    board.addDisc(Disc::Colour::white, 2);
    board.addDisc(Disc::Colour::black, 3);
    board.addDisc(Disc::Colour::white, 4);
    board.addDisc(Disc::Colour::black, 5);
    board.addDisc(Disc::Colour::white, 6);

    board.addDisc(Disc::Colour::black, 3);

    //expected answer for this board format = 3
    //(taken from http://connect4.gamesolver.org/?pos=12345674)
    auto nMovesRemaining{17};
    //    ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::black);
    //REQUIRE(ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::white) == 3);

//    board.reset();

//    board.addDisc(Disc::Colour::white, 0);
//    board.addDisc(Disc::Colour::black, 1);
//    board.addDisc(Disc::Colour::white, 2);
//    board.addDisc(Disc::Colour::black, 3);
//    board.addDisc(Disc::Colour::white, 4);
//    board.addDisc(Disc::Colour::black, 5);
//    board.addDisc(Disc::Colour::white, 6);
//    board.addDisc(Disc::Colour::black, 2);

//    REQUIRE(ai.calculateNextMove(board, nMovesRemaining, Disc::Colour::white) == 2);


    //board.reset();


    //    }

}

