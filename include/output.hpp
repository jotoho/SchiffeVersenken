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

#ifndef INCLUDE_GUARD_OUTPUT_HPP
#define INCLUDE_GUARD_OUTPUT_HPP

#include <iostream>
#include <unordered_map>
#include "./fieldinfo.hpp"

// Information needed to represent state of field on screen
struct BoardFieldFormat {
    const char symbol;
    const char* const colorCode;
    BoardFieldFormat(const char, const char* const);
};

using OutputTranslationTable =
    const std::unordered_map<const FieldValue, const BoardFieldFormat>&;

// this translation table only shows revealed ship parts or misses.
const OutputTranslationTable defaultTranslationTable();

// this one shows everything defaultTranslationTable does,
// plus all ship parts
const OutputTranslationTable transparentTranslationTable();

// Gets the version from global-config.hpp and prints it to console
void writeProgramInfo(std::ostream& out = std::cout);
// Stops the game and waits for player input
void waitForReturn();
// After every move this function is called to refresh the Board
void refreshBoard(const BoardType& playerBoard,
                  const BoardType& computerBoard,
                  const BoardType& currentBoard,
                  const char* const boardDiscription,
                  OutputTranslationTable translationTable);
// Clears the screen
void clearScreen();
// Counts ships on board
std::size_t shipCount(const BoardType& board);
// Prints amount of ships from each player
void healthBar(const BoardType& playerBoard, const BoardType& computerBoard);
// Prints horizontal separator of correct length
void printLine();
// Prints column labels and separators between them
void printNumbers();
// Prints basic usage instructions
void printTutorial();
// Prints the main body of the given game board
// using the settings in
void printGameBoard(const BoardType& board,
                    const OutputTranslationTable translationTable,
                    const char defaultChar = ' ');

#endif  // INCLUDE_GUARD_OUTPUT_HPP
