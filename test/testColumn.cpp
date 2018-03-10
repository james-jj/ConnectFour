////
////  testColumn.cpp
////  ConnectFour
////
////  Created by James Johnstone on 05/08/2017.
////  Copyright © 2017 James Johnstone. All rights reserved.
////
//#include "catch.hpp"
//#include "Column.h"

//enum class testStatus{ pass, fail };

////test to validate that a disc can't be added to a full column
//int addDiscToFullCol(int columnHeight)
//{
//    int columnID = 0;
//    Column column(columnHeight,columnID);
    
//    for(int row = 0; row < columnHeight+1; ++row)
//    {
//        column.addDisc(Disc::Colour::white);
//    }
    
//    return column.getCurrentHeight();
//};

////test to validate that isFull is set to true when a column is full
//bool validateIsFull()
//{
//    int columnHeight = 6;
//    int columnID = 0;
//    Column column(columnHeight,columnID);
    
//    for(int row = 0; row < columnHeight; ++row)
//    {
//        column.addDisc(Disc::Colour::white);
//    }
    
//    return column.getIsFull();
//}

//TEST_CASE("A disc can't be added to a full column")
//{
//    int columnHeight = 6;
//    REQUIRE( addDiscToFullCol(columnHeight) == columnHeight );
    
//    SECTION("isFull is set to true when column is full of discs")
//    {
//        REQUIRE( validateIsFull() == true );
//    }
//}
