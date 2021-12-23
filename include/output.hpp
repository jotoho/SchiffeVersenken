#ifndef INCLUDE_GUARD_OUTPUT_HPP
#define INCLUDE_GUARD_OUTPUT_HPP

#include <unordered_map>
#include "./fieldinfo.hpp"

const std::unordered_map<const FieldValue, const char>&
defaultTranslationTable();

const std::unordered_map<const FieldValue, const char>&
transparentTranslationTable();

void clearScreen();
void printLine();
void printNumbers();
void printGameBoard(
    const BoardType& board,
    const std::unordered_map<const FieldValue, const char>& translationTable,
    const char defaultChar = ' ');

#endif  // INCLUDE_GUARD_OUTPUT_HPP
