#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>

#include "../include/fieldinfo.hpp"

void clearScreen() {
#if _WIN32
    system("cls");
#elif __linux__ || __unix__ || __APPLE__
    [[maybe_unused]] const auto test = system("clear");
#endif
}

void printGameBoard(const BoardType& board) {
    printf("   ");
    for (size_t lineIndex = 0; lineIndex < rows; lineIndex++) {
        std::cout << ' ' << lineIndex + 1 << ' ';
    }
    printf("    \n");

    // Rows
    for (size_t lineIndex = 0; lineIndex < rows; lineIndex++) {
        printf(" %c ", static_cast<char>('A' + lineIndex));
        // Columns
        for (size_t columnIndex = 0; columnIndex < columns; columnIndex++) {
            char chars[] = {
                ' ',
                board[lineIndex][columnIndex] == FieldValue::SHIP_HIT ? 'X'
                                                                      : ' ',
                ' '};
            printf("%s", chars);
        }
        printf(" %c\n", static_cast<char>('A' + lineIndex));
    }

    printf("   ");
    for (size_t lineIndex = 0; lineIndex < rows; lineIndex++) {
        std::cout << ' ' << lineIndex + 1 << ' ';
    }
    printf("   ");
}

int main() {
    BoardType board;
    for (auto& innerArray : board) {
        std::fill(innerArray.begin(), innerArray.end(), FieldValue::EMPTY);
    }
    printGameBoard(board);
    return EXIT_SUCCESS;
}
