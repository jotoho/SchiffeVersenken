#include <cstdlib>
#include "../include/board-generator.hpp"
#include "../include/output.hpp"

int main() {
    BoardType board = generateGameBoardRandom();
    printGameBoard(board, transparentTranslationTable());
    return EXIT_SUCCESS;
}
