#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../include/board-generator.hpp"
#include "../include/gamelogic.hpp"
#include "../include/output.hpp"

int main() {
    // Give basic instructions to player
    printTutorial();

    // Initialize RNG
    std::srand(std::time(nullptr));

    // Generate boards for both players
    auto playerBoard = generateGameBoardRandom();
    auto computerBoard = generateGameBoardRandom();

    // Try to determine the winner
    const WinnerID winnerID = playGame(playerBoard, computerBoard);

    // Announce winner
    std::cout << "Player " << std::to_string(winnerID) << " has won!\n";
    return EXIT_SUCCESS;
}
