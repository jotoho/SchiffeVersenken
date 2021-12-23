#include <cstdlib>
#include "../include/output.hpp"
#include "../include/board-generator.hpp"

int main() {
    BoardType board = generateGameBoardRandom();
    printGameBoard(board, transparentTranslationTable());
    return EXIT_SUCCESS;
}
