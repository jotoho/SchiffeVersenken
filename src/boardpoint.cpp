// SPDX-License-Identifier: GPL-3.0-or-later
/*
SchiffeVersenken - An implementation of Battleships
Copyright (C) 2022 SchiffeVersenken contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <algorithm>
#include <stdexcept>

#include "boardpoint.hpp"

/*
    Constructor for BoardPoint. It checks if the given coordinates are
    in-bounds based on the global board size settings.
*/
BoardPoint::BoardPoint(const std::size_t x, const std::size_t y) : x(x), y(y) {
    if (x >= BoardDimensions.columns)
        throw std::invalid_argument{
            "Attempt to create BoardPoint with too high column number detected "
            "(received: " +
            std::to_string(x) +
            ", max: " + std::to_string(BoardDimensions.columns - 1) + ')'};
    else if (y >= BoardDimensions.rows)
        throw std::invalid_argument{
            "Attempt to create BoardPoint with too high row number detected "
            "(received: " +
            std::to_string(y) +
            ", max: " + std::to_string(BoardDimensions.rows - 1) + ')'};
}

/*
    Attempts to add the coordinates of two points together.
    Since BoardPoint is immutable, this creates a new BoardPoint.
    Throws std::invalid_argument if resulting point would be out-of-bounds.
*/
BoardPoint BoardPoint::operator+(const BoardPoint& otherPoint) const {
    return BoardPoint{this->x + otherPoint.x, this->y + otherPoint.y};
}

/*
    Attempts to subtract coordinates in other point from this one.
    Throws std::range_error if this would have caused an underflow
    or std::invalid_argument if the resulting point is out-of-bounds.
*/
BoardPoint BoardPoint::operator-(const BoardPoint& otherPoint) const {
    // Leaving out the braces on this if will make gcc 11.1.0 not correctly
    // connect it with the else-block
    if (this->x < otherPoint.x || this->y < otherPoint.y) {
        throw std::range_error{
            "Point does not exist on board (coords would have "
            "underflowed)"};
    } else
        return BoardPoint{this->x - otherPoint.x, this->y - otherPoint.y};
}

/*
    Tests if two BoardPoints are identical.
    Return true if yes, otherwise false.
*/
bool BoardPoint::operator==(const BoardPoint& otherPoint) const {
    return this->x == otherPoint.x && this->y == otherPoint.y;
}

/*
    Given a start point, an end point and the direction the end point
    is in from the perspective of the start point, this function
    generates the corresponsing BoardPointRange between both points
    and including both.
*/
BoardPointRange generatePointRangeBetween(const BoardPoint& startPoint,
                                          const BoardPoint& endPoint,
                                          const CardinalDirection direction) {
    BoardPointRange shipPoints;
    shipPoints.emplace_back(startPoint);

    // While list does not contain endPoint
    while (std::find(shipPoints.begin(), shipPoints.end(), endPoint) ==
           shipPoints.end()) {
        const auto lastPoint = shipPoints.at(shipPoints.size() - 1);
        shipPoints.emplace_back(stepsFromPoint(lastPoint, direction, 1));
    }

    return shipPoints;
}

/*
    Uses arithmetic boardpoint operators to attempt generating a board point
    a certain distance away from the given point in the specified direction.
*/
BoardPoint stepsFromPoint(const BoardPoint& originPoint,
                          const CardinalDirection direction,
                          const std::size_t numberOfSteps) {
    switch (direction) {
        case CardinalDirection::NORTH:
            return originPoint - BoardPoint{0, numberOfSteps};
        case CardinalDirection::EAST:
            return originPoint + BoardPoint{numberOfSteps, 0};
        case CardinalDirection::SOUTH:
            return originPoint + BoardPoint{0, numberOfSteps};
        case CardinalDirection::WEST:
            return originPoint - BoardPoint{numberOfSteps, 0};
        default:
            throw std::invalid_argument{"Invalid direction was provided"};
    }
}

/*
    Looks up the FieldValue at the given point on the given board and
    then returns a reference.
    This is to avoid duplicate, easily breakable code.
*/
FieldValue& getRefFromPoint(BoardType& board, const BoardPoint& point) {
    return board[point.y][point.x];
}

// Const overload
const FieldValue& getRefFromPoint(const BoardType& board,
                                  const BoardPoint& point) {
    return board[point.y][point.x];
}
