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

void printLine(){
    constexpr size_t length = BoardDimensions.columns*4+3;
    for(size_t dash = 0;dash<length;dash++)
        putc('-',stdout);
    putc('\n',stdout);
}

void printNumbers(){
    printf("  |");
    for (size_t lineIndex = 0; lineIndex < BoardDimensions.rows; lineIndex++) {
        std::cout << ' ' << lineIndex + 1;
        if (lineIndex != BoardDimensions.rows - 1)
            std::cout << " |";
    }
    printf("|\n");
}

void printGameBoard(const BoardType& board) {
    printNumbers();
    // Rows
    for (size_t lineIndex = 0; lineIndex < BoardDimensions.rows; lineIndex++) {
        printLine();
        printf(" %c|", static_cast<char>('A' + lineIndex));
        // Columns
        for (size_t columnIndex = 0; columnIndex < BoardDimensions.columns; columnIndex++) {
            char chars[] = {
                ' ',
                board[lineIndex][columnIndex] == FieldValue::SHIP_HIT ? 'X'
                                                                      : ' ',
                ' ', '\0'};
            printf("%s|", chars);
        }
        printf("%c\n", static_cast<char>('A' + lineIndex));
    }
    printLine();
    printNumbers();
}

int main() {
    BoardType board;
    for (auto& innerArray : board) {
        std::fill(innerArray.begin(), innerArray.end(), FieldValue::EMPTY);
    }
    printGameBoard(board);
    return EXIT_SUCCESS;
}
