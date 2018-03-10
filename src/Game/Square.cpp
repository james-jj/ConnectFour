//
//  Square.cpp
//  ConnectFour
//
//  Created by James Johnstone on 05/08/2017.
//  Copyright © 2017 James Johnstone. All rights reserved.
//
#include <tuple>
#include <gsl/gsl>
#include "Square.h"
#include "Disc.h"

Square::Square(std::tuple<int, int> _position) : position{_position}
{
    Expects(std::get<0>(position) >= 0 && std::get<1>(position) >= 0);
}

//add either a white or black disc to the square
void Square::addDisc(const Disc::Colour& discColour)
{
    switch(discColour)
    {
        case(Disc::Colour::white): status = Square::Status::containsWhite; break;
        case(Disc::Colour::black): status = Square::Status::containsBlack; break;
    }
}

//get (column,row) coordinates of the current square
std::tuple<int, int> Square::getPosition() const
{
    return position;
}

Square::Status Square::getSquareStatus() const
{
    return status;
}

