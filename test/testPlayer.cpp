////
////  testPlayer.cpp
////  ConnectFour
////
////  Created by James Johnstone on 05/08/2017.
////  Copyright © 2017 James Johnstone. All rights reserved.
////
//#include <iostream>
//#include "catch.hpp"
//#include "Player.h"
//#include "Disc.h"

//int testCorrectValue(int selectedColumn)
//{
//    Player player(Disc::Colour::black, 1, true);
    
//    //redirect std input for this unit test
//    std::streambuf* orig = std::cin.rdbuf();
//    std::istringstream input(std::to_string(selectedColumn));
//    std::cin.rdbuf(input.rdbuf());
//    int selectedValue = player.selectColumn();
    
//    //restore original std input
//    std::cin.rdbuf(orig);

//    return selectedValue;
//}

//TEST_CASE("Correct values returned from player input")
//{
//    int selectedColumn = 1;
//    REQUIRE( testCorrectValue(selectedColumn) == --selectedColumn );
   
//    selectedColumn = 7;
//    REQUIRE( testCorrectValue(selectedColumn) == --selectedColumn );
//}

///*
//int selectColumnLT1()
//{
//    Player player(DiscColour::white, 2, 1);
    
//    //redirect std input for this unit test
//    std::streambuf* orig = std::cin.rdbuf();
//    std::istringstream input("0");
//    std::cin.rdbuf(input.rdbuf());
//    player.selectColumn();
//    std::cin.rdbuf(orig);
    
//    player.selectColumn(-1);
    
//}

//TEST_CASE("Player can only select column ID >= 1")
//{
//    int columnHeight = 6;
//    REQUIRE( addDiscToFullCol(columnHeight) == columnHeight );
    
//    SECTION("isFull is set to true when column is full of discs")
//    {
//        REQUIRE( validateIsFull() == true );
//    }
//}
//*/
