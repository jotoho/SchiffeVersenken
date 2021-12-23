#include <cstdlib>
#include "../include/output.hpp"

int main() {
    BoardType board;
    for (auto& innerArray : board) {
        std::fill(innerArray.begin(), innerArray.end(), FieldValue::EMPTY);
    }
    printGameBoard(board);
    return EXIT_SUCCESS;
}
