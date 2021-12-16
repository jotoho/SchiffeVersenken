#include "../include/ai.hpp"
#include "../include/board-generator.hpp"
#include "../include/output.hpp"

int main() {
    BoardType testBoard = generateGameBoardRandom();

    printGameBoard(testBoard, transparentTranslationTable());

    for (int i = 0; i < 10; i++) {
        aiShotRandom(testBoard);
    }

    printGameBoard(testBoard, transparentTranslationTable());
}