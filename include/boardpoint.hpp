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

#ifndef INCLUDE_GUARD_BOARDPOINT_HPP
#define INCLUDE_GUARD_BOARDPOINT_HPP

#include <vector>
#include "fieldinfo.hpp"

// Boundschecked abstraction for points on the game board
struct BoardPoint {
    // Horizontal position; 0 is the left border
    const std::size_t x;
    // Vertical position; 0 is the upper border
    const std::size_t y;

    BoardPoint() = delete;
    BoardPoint(const std::size_t x, const std::size_t y);

    BoardPoint operator+(const BoardPoint& otherPoint) const;
    BoardPoint operator-(const BoardPoint& otherPoint) const;

    bool operator==(const BoardPoint& otherPoint) const;
};

// Collection of BoardPoints in a line (horizontal or vertical)
using BoardPointRange = std::vector<BoardPoint>;
// Helper enum for handling direction. North is defined as up on screen.
enum class CardinalDirection : std::uint_least8_t { NORTH, EAST, SOUTH, WEST };

// Generates BoardPointRange for area between given points.
// Direction is that from startPoint to endPoint
BoardPointRange generatePointRangeBetween(const BoardPoint& startPoint,
                                          const BoardPoint& endPoint,
                                          const CardinalDirection direction);

// Attempts to return BoardPoint a certain distance away from origin
// in the given direction
BoardPoint stepsFromPoint(const BoardPoint& originPoint,
                          const CardinalDirection direction,
                          const std::size_t numberOfSteps);

FieldValue& getRefFromPoint(BoardType& board, const BoardPoint& point);
const FieldValue& getRefFromPoint(const BoardType& board,
                                  const BoardPoint& point);

#endif  // INCLUDE_GUARD_BOARDPOINT_HPP
