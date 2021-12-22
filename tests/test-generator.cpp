#include <ctime>

#include "../src/board-generator.cpp"
#include "../src/output.cpp"

int main() {
    std::srand(std::time(nullptr));
    printGameBoard(generateGameBoardRandom());
}
