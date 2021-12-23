#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_map>

#include "../include/fieldinfo.hpp"

void clearScreen() {
#if _WIN32
    system("cls");
#elif __linux__ || __unix__ || __APPLE__
    [[maybe_unused]] const auto test = system("clear");
#endif
}

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

void printNumbers() {
    const auto basicWidth =
        static_cast<std::size_t>(std::log10(BoardDimensions.columns)) + 1U;
    printf("  | ");
    for (std::size_t lineIndex = 0; lineIndex < BoardDimensions.columns;
         lineIndex++) {
        std::cout << std::setfill('0')
                  << std::setw(basicWidth % 2 == 0 ? basicWidth + 1U
                                                   : basicWidth)
                  << lineIndex + 1;
        if (lineIndex != BoardDimensions.columns - 1)
            std::cout << " | ";
    }
    printf(" |\n");
}

void printGameBoard(
    const BoardType& board,
    const std::unordered_map<const FieldValue, const char>& translationTable,
    const char defaultChar = ' ') {
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
                std::cout << translationTable.at(fieldValue);
            } catch (const std::out_of_range& e) {
                std::cout << defaultChar;
            }
            std::cout << paddingStr << '|';
        }
        printf("%c\n", static_cast<char>('A' + lineIndex));
    }
    printLine();
    printNumbers();
}

const std::unordered_map<const FieldValue, const char>&
transparentTranslationTable() {
    static const std::unordered_map<const FieldValue, const char>
        translationTable{{FieldValue::SHIP_HIT, 'X'},
                         {FieldValue::SHIP, '#'},
                         {FieldValue::MISS, '~'}};
    return translationTable;
}

const std::unordered_map<const FieldValue, const char>&
defaultTranslationTable() {
    static const std::unordered_map<const FieldValue, const char>
        translationTable{{FieldValue::SHIP_HIT, 'X'}, {FieldValue::MISS, '~'}};
    return translationTable;
}
