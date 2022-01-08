#ifndef INCLUDE_GUARD_OUTPUT_HPP
#define INCLUDE_GUARD_OUTPUT_HPP

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

void clearScreen();
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
