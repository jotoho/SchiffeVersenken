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

#include "../include/output.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_map>

#include "../include/fieldinfo.hpp"
#include "../include/global-config.hpp"

void clearScreen() {
#if _WIN32
    system("cls");
#elif __linux__ || __unix__ || __APPLE__
    [[maybe_unused]] const auto test = system("clear");
#endif
}

/*
    Counts ships on board
*/
std::size_t shipCount(const BoardType& board) {
    std::size_t ships = 0;
    for (const auto& segment : board)
        ships += std::count(segment.begin(), segment.end(), FieldValue::SHIP);
    return ships;
}
/*
    Used to count the ships on both boards and displays them on the screen
*/
void healthBar(const BoardType& playerBoard, const BoardType& computerBoard) {
    const std::size_t playerHealth = shipCount(playerBoard);
    const std::size_t computerHealth = shipCount(computerBoard);
    std::cout << std::setfill(' ') << std::setw(3) << "(Player 1) Computer "
              << computerHealth << " : " << playerHealth
              << " Human (Player 2)\n\n";
}
/*
    Wait for the player to confirm by pressing Return (LF).

    All other inputs until then are ignored.
*/
void waitForReturn() {
    // Emit notice to stdout
    std::puts("Press Return key to continue...");
    std::fflush(stdout);

    while (true) {
        switch (std::getchar()) {
            case '\n':
            case EOF:
                return;
            default:
                continue;
        }
    }
}

/*
    Outputs basic program name and version to screen
*/
void writeProgramInfo(std::ostream& out) {
    out << "SchiffeVersenken " << GlobalConf.version << '\n' << std::endl;
}

/*
    Used to update the board on screen
*/
void refreshBoard(const BoardType& playerBoard,
                  const BoardType& computerBoard,
                  const BoardType& currentBoard,
                  const char* const boardDiscription,
                  OutputTranslationTable translationTable) {
    if (&currentBoard != &playerBoard && &currentBoard != &computerBoard) {
        throw std::invalid_argument{
            "Reference to wrong board was passed to refreshBoard"};
    }
    clearScreen();
    writeProgramInfo(std::cout);
    healthBar(playerBoard, computerBoard);
    std::cout << boardDiscription << '\n';
    printGameBoard(currentBoard, translationTable);
    std::cout << '\n';
}

/*
    Used to print lines between rows
*/
void printLine() {
    const std::size_t columnLabelWidthRaw =
        static_cast<std::size_t>(std::log10(BoardDimensions.columns)) + 1U;
    const std::size_t columnLabelWidth = columnLabelWidthRaw % 2 == 0
                                             ? columnLabelWidthRaw + 1U
                                             : columnLabelWidthRaw;
    const std::size_t length =
        BoardDimensions.columns * (columnLabelWidth + 2U + 1U) + 4U;

    for (std::size_t dash = 0; dash < length; dash++)
        putc('-', stdout);
    putc('\n', stdout);
}
/*
    Used to print numbers for each column
*/
void printNumbers() {
    const auto basicWidth =
        static_cast<std::size_t>(std::log10(BoardDimensions.columns)) + 1U;
    printf("  | ");
    for (std::size_t lineIndex = 0; lineIndex < BoardDimensions.columns;
         lineIndex++) {
        // Determens if additional padding is needed based on basicWidth
        std::cout << std::setfill('0')
                  << std::setw(basicWidth % 2 == 0 ? basicWidth + 1U
                                                   : basicWidth)
                  << lineIndex + 1;
        if (lineIndex != BoardDimensions.columns - 1)
            std::cout << " | ";
    }
    printf(" |\n");
}

/*
    Used to print a short tutorial on game start
*/
void printTutorial() {
    clearScreen();
    for (size_t lines = 0; lines <= 70; lines++)
        std::cout << '-';
    std::cout << '\n';
    writeProgramInfo(std::cout);
    std::cout
        << "Each turn you will have the chance to fire once.\n"
           "If you hit an enemy ship you can shoot again.\n"
           "Please enter the coordinates letter first then the number.\n\n"
           "Ships  are displayed with #\n"
           "Misses are displayed with ~\n"
           "Hits   are displayed with X\n\n"
           "The bugtracker and sourcecode can be found here:\n"
           "https://github.com/jotoho/SchiffeVersenken\n\n";
    for (size_t lines = 0; lines <= 70; lines++)
        std::cout << '-';
    std::cout << '\n';
    waitForReturn();
}
/*
    Used to print the game board and the ships
    plus their current state in the game
*/
void printGameBoard(const BoardType& board,
                    const OutputTranslationTable translationTable,
                    const char defaultChar) {
    // Determens if additional padding is needed based on the amount of columns
    const std::size_t paddingLength =
        (static_cast<std::size_t>(std::log10(BoardDimensions.columns)) + 3U) /
        2U;
    std::string paddingStr{};
    for (std::size_t i = 0; i < paddingLength; i++)
        paddingStr.insert(paddingStr.begin(), ' ');

    printNumbers();
    // Rows
    for (std::size_t lineIndex = 0; lineIndex < BoardDimensions.rows;
         lineIndex++) {
        printLine();
        printf(" %c|", static_cast<char>('A' + lineIndex));
        // Columns
        for (std::size_t columnIndex = 0; columnIndex < BoardDimensions.columns;
             columnIndex++) {
            const auto fieldValue = board[lineIndex][columnIndex];
            std::cout << paddingStr;
            try {
                // Gets the fitting symbol and color code from
                // OutputTranslationTable based on the fieldValue
                const auto& formatData = translationTable.at(fieldValue);
                std::cout << formatData.colorCode << formatData.symbol
                          << "\033[0m";
            } catch (const std::out_of_range& e) {
                std::cout << defaultChar << "\033[0m";
            }
            std::cout << paddingStr << '|';
        }
        printf("%c\n", static_cast<char>('A' + lineIndex));
    }
    printLine();
    printNumbers();
}

BoardFieldFormat::BoardFieldFormat(const char symbol,
                                   const char* const colorCode)
    : symbol(symbol), colorCode(colorCode) {}

/*
    Stores the symbol and the colorCode for every FieldValue
    Player board
*/
OutputTranslationTable transparentTranslationTable() {
    static const std::unordered_map<const FieldValue, const BoardFieldFormat>
        translationTable{
            {FieldValue::SHIP_HIT, BoardFieldFormat{'X', "\033[1;31m"}},
            {FieldValue::SHIP, BoardFieldFormat{'#', "\033[1;32m"}},
            {FieldValue::MISS, BoardFieldFormat{'~', "\033[1;34m"}}};
    return translationTable;
}
/*
    Stores the symbol and the colorCode for every FieldValue
    Computer board
*/
OutputTranslationTable defaultTranslationTable() {
    static const std::unordered_map<const FieldValue, const BoardFieldFormat>
        translationTable{
            {FieldValue::SHIP_HIT, BoardFieldFormat{'X', "\033[1;31m"}},
            {FieldValue::MISS, BoardFieldFormat{'~', "\033[1;34m"}}};
    return translationTable;
}
