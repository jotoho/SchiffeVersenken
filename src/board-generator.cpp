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
#include <random>
#include <stdexcept>
#include <vector>
#include "../include/boardpoint.hpp"

/*
    Generates and returns a basic empty game board with all fields
    set to empty.
*/
BoardType generateGameBoardEmpty() {
    BoardType board{};
    for (auto& row : board)
        std::fill(row.begin(), row.end(), FieldValue::EMPTY);
    return board;
}

// file-internal function for generating random value of 32-bit length
static std::uint_fast32_t genRandom32bitVal() {
    // std::rand() alone doesn't give enough guarantees regarding the size of
    // RAND_MAX for my purposes
    static auto randomNumberGenerator =
        std::minstd_rand{static_cast<unsigned int>(std::rand())};
    return randomNumberGenerator();
}

// file-internal function for generating random value of 64-bit length
static std::uint_fast64_t genRandom64bitVal() {
    // Fuse two random 32-bit values into one 64-bit uint
    return (genRandom32bitVal() << 32) | genRandom32bitVal();
}

/*
    This function attempts to set an adjacent field to PLACEHOLDER
    but will simply return without doing anything, if it encounters an error.
*/
static void attemptPlacingPlaceholder(BoardType& board,
                                      const BoardPoint& center,
                                      const CardinalDirection direction) {
    try {
        const auto adjacentPoint = stepsFromPoint(center, direction, 1);
        auto& adjacentPointValue = getRefFromPoint(board, adjacentPoint);
        if (adjacentPointValue == FieldValue::EMPTY)
            adjacentPointValue = FieldValue::PLACEHOLDER;
    } catch (const std::exception& ignored) {
    }
}

/*
    Checks if the points included in a BoardPointRange are all EMPTY
    on the given board.
    For the purposes of this method placeholders do not count as empty.

    Return value: true if all are EMPTY, otherwise false
*/
static bool isThisAreaOnBoardEmpty(const BoardType& board,
                                   const BoardPointRange& points) {
    for (const auto& point : points)
        if (getRefFromPoint(board, point) != FieldValue::EMPTY)
            return false;
    return true;
}

/*
    Writes a ship into the BoardPointRange given on the board
    and attempts to fill in the PLACEHOLDERs around it.

    This function assumes that all given points are empty on
    this board.
*/
static void writeShipToBoard(BoardType& board,
                             const BoardPointRange& shipPoints) {
    for (const auto& point : shipPoints) {
        getRefFromPoint(board, point) = FieldValue::SHIP;

        // Try placing placeholder in empty slots around ship
        for (const auto directionPlaceholder :
             {CardinalDirection::NORTH, CardinalDirection::EAST,
              CardinalDirection::SOUTH, CardinalDirection::WEST})
            attemptPlacingPlaceholder(board, point, directionPlaceholder);
    }
}

/*
    Selects a random valid BoardPoint and returns it.
*/
static BoardPoint chooseRandomBoardPoint() {
    return {
        static_cast<std::size_t>(genRandom64bitVal()) % BoardDimensions.columns,
        static_cast<std::size_t>(genRandom64bitVal()) % BoardDimensions.rows};
}

/*
    Specialized exception type for when lots of attempts to
    place ships have failed and we assume that not enough space
    remains to completely populate the board.
*/
struct InsufficientBoardSpaceError : std::runtime_error {
    InsufficientBoardSpaceError(const std::string msg)
        : std::runtime_error(msg) {}
};

/*
    Attempts to place a ship with the given size anywhere on the board.

    If the function believes that this is impossible it can throw
    InsufficientBoardSpaceError.
*/
static void randomlyPlaceShip(BoardType& board, const std::size_t shipLength) {
    // This will repeat until the placement was successful
    constexpr std::uint_fast32_t maxAttempts = 1000;
    bool placementSuccessful = false;

    for (std::uint_fast32_t placementAttempt = 1;
         placementAttempt <= maxAttempts && !placementSuccessful;
         placementAttempt++) {
        const BoardPoint selectedPoint = chooseRandomBoardPoint();
        const CardinalDirection direction =
            static_cast<CardinalDirection>(std::rand() % 4);

        try {
            const BoardPoint endPoint =
                stepsFromPoint(selectedPoint, direction, shipLength - 1);

            const BoardPointRange shipPoints =
                generatePointRangeBetween(selectedPoint, endPoint, direction);

            // Check if placement is possible
            if (!isThisAreaOnBoardEmpty(board, shipPoints))
                continue;

            // Assume everything checks out and set Fields
            writeShipToBoard(board, shipPoints);

            placementSuccessful = true;

        } catch (const std::invalid_argument& e) {
            continue;
        } catch (const std::range_error& e) {
            continue;
        }
    }

    if (!placementSuccessful)
        throw InsufficientBoardSpaceError{
            ("Not enough space to create a ship with length " +
             std::to_string(shipLength) + " (tried " +
             std::to_string(maxAttempts) + " times)")};
}

/*
    This function requests all the required ships to be randomly placed
    on the board.

    Returns the board if successful. Throws an InsufficientBoardSpaceError
    exception otherwise.
*/
static BoardType attemptGeneratingRandomBoard() {
    auto board = generateGameBoardEmpty();
    for (std::size_t shipLength = 2; shipLength < ShipDistribution.size();
         shipLength++)
        for (std::uint_fast8_t shipsPlaced = 0;
             shipsPlaced < ShipDistribution[shipLength]; shipsPlaced++)
            randomlyPlaceShip(board, shipLength);
    return board;
}

/*
    Tries to randomly generate a game board with all required ships.

    Return value is the board.

    May throw InsufficientBoardSpaceError if it believes there are
    too many or too large ships for the provided board space.
*/
BoardType generateGameBoardRandom() {
    constexpr std::uint_least8_t maxFailures = 100;
    std::uint_least8_t failedAttempts = 0;

    while (true) {
        try {
            return attemptGeneratingRandomBoard();
        } catch (const InsufficientBoardSpaceError& unused) {
            if (failedAttempts++ >= maxFailures)
                throw InsufficientBoardSpaceError{
                    "Populating board with desired ships is not possible"};
        }
    }
}
