#include <cstdlib>
#include <ctime>

#include "../include/board-generator.hpp"
#include "../include/output.hpp"

int main() {
    std::srand(std::time(nullptr));
    printGameBoard(generateGameBoardRandom(), transparentTranslationTable());
}
