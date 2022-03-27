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

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include "../include/boardpoint.hpp"

/*
    Shoots at adjacent field of the last hit location.
    Calls itself on success to continue attempts at hitting the ships,
    otherwise ends after one miss.
*/
void hitShip(BoardType& board, const BoardPoint& lastShot) {
    bool error;
    do {
        error = false;
        try {
            const auto newLocation = stepsFromPoint(
                lastShot, static_cast<CardinalDirection>(rand() % 4), 1);

            switch (getRefFromPoint(board, newLocation)) {
                case FieldValue::EMPTY:
                    [[fallthrough]];
                case FieldValue::PLACEHOLDER:
                    getRefFromPoint(board, newLocation) = FieldValue::MISS;
                    break;
                case FieldValue::SHIP:
                    getRefFromPoint(board, newLocation) = FieldValue::SHIP_HIT;
                    hitShip(board, newLocation);
                    break;
                case FieldValue::MISS:
                    [[fallthrough]];
                case FieldValue::SHIP_HIT:
                    hitShip(board, lastShot);
                    break;
            }
        } catch (const std::invalid_argument& unused) {
            error = true;
        } catch (const std::range_error& unused) {
            error = true;
        }
    } while (error);
}

/*
    Randomly shoots at the board and then calls hitShip for successive
    shots if first one hit.
    Return true if first shot hit, otherwise false.
*/
bool aiShotRandom(BoardType& board) {
    const BoardPoint target{std::rand() % BoardDimensions.columns,
                            std::rand() % BoardDimensions.rows};

    switch (getRefFromPoint(board, target)) {
        case FieldValue::EMPTY:
            [[fallthrough]];
        case FieldValue::PLACEHOLDER:
            getRefFromPoint(board, target) = FieldValue::MISS;
            return false;
        case FieldValue::SHIP:
            getRefFromPoint(board, target) = FieldValue::SHIP_HIT;
            hitShip(board, target);
            return true;
        case FieldValue::MISS:
            [[fallthrough]];
        case FieldValue::SHIP_HIT:
            return aiShotRandom(board);
        default:
            std::cerr << "aiShotRandom: Unexpected value in field, closing "
                         "application."
                      << std::endl;
            std::exit(EXIT_FAILURE);
    }
}
