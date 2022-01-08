#ifndef INCLUDE_GUARD_OUTPUT_HPP
#define INCLUDE_GUARD_OUTPUT_HPP

#include <unordered_map>
#include "./fieldinfo.hpp"

struct BoardFieldFormat {
    const char symbol;
    const char* const colorCode;
    BoardFieldFormat(const char, const char* const);
};

using OutputTranslationTable =
    const std::unordered_map<const FieldValue, const BoardFieldFormat>&;

const OutputTranslationTable defaultTranslationTable();

const OutputTranslationTable transparentTranslationTable();

void clearScreen();
void printLine();
void printNumbers();
void printTutorial();
void printGameBoard(const BoardType& board,
                    const OutputTranslationTable translationTable,
                    const char defaultChar = ' ');

#endif  // INCLUDE_GUARD_OUTPUT_HPP
