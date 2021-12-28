#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

#include "../include/ai.hpp"
#include "../include/board-generator.hpp"
#include "../include/boardpoint.hpp"
#include "../include/gamelogic.hpp"
#include "../include/input.hpp"
#include "../include/output.hpp"

int main() {
    std::srand(std::time(nullptr));
    auto playerBoard = generateGameBoardRandom();
    auto computerBoard = generateGameBoardRandom();

    for (unsigned round = 1;
         !checkWinner(playerBoard, computerBoard) &&
         round < std::numeric_limits<decltype(round)>::max();
         round++) {

        std::cout << "The enemy's field:\n";
        printGameBoard(computerBoard, defaultTranslationTable());
        std::cout << '\n';

        std::cout << "Where do you want to shoot? ";
        std::string userInput{};
        std::getline(std::cin, userInput);
        clearScreen();
        auto& target =
            getRefFromPoint(computerBoard, inputTranslator(userInput));

        switch (target) {
            case FieldValue::MISS:
            case FieldValue::SHIP_HIT:
                std::cout << "You already shot there once!\n";
                round--;
                continue;
            case FieldValue::EMPTY:
            case FieldValue::PLACEHOLDER:
                //std::cout << "Missed!\n";
                target = FieldValue::MISS;
                break;
            case FieldValue::SHIP:
                //std::cout << "Hit!\n";
                target = FieldValue::SHIP_HIT;
                break;
            default:
                std::cerr << "Invalid state of field on board. Terminating!\n";
                std::exit(EXIT_FAILURE);
        }

        if (checkWinner(playerBoard, computerBoard))
            break;

        aiShotRandom(playerBoard);
        std::cout << "Your board:\n";
        printGameBoard(playerBoard, transparentTranslationTable());
        std::cout << "\nPress Enter to continue...\n";
        while(std::getchar() != '\n');
        clearScreen();
    }

    const auto winnerID = checkWinner(playerBoard, computerBoard);
    if (winnerID == 0) {
        std::cerr << "Reached maximum round. Terminating!" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Player " << winnerID
              << " has won!\n";
    return EXIT_SUCCESS;
}
