#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../include/board-generator.hpp"
#include "../include/gamelogic.hpp"

int main() {
    // Initialize RNG
    std::srand(std::time(nullptr));

    // Generate boards for both players
    auto playerBoard = generateGameBoardRandom();
    auto computerBoard = generateGameBoardRandom();

    // Try to determine the winner
    const auto winnerID = playGame(playerBoard, computerBoard);

    // Announce winner
    std::cout << "Player " << winnerID << " has won!\n";
    return EXIT_SUCCESS;
}
