#include "../include/gamelogic.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include "../include/ai.hpp"
#include "../include/boardpoint.hpp"
#include "../include/fieldinfo.hpp"
#include "../include/global-config.hpp"
#include "../include/input.hpp"
#include "../include/output.hpp"

void writeProgramInfo(std::ostream& out) {
    out << "SchiffeVersenken version " << GlobalConf.version << '\n'
        << std::endl;
}

static bool hasLost(const BoardType& board) {
    for (const auto& segment : board)
        if (std::find(segment.begin(), segment.end(), FieldValue::SHIP) !=
            segment.end())
            // Contains >= 1 ship parts
            return false;

    // No ships are left
    return true;
}

WinnerID checkWinner(const BoardType& boardPlayer1,
                     const BoardType& boardPlayer2) {
    const bool player1Lost = hasLost(boardPlayer1);
    const bool player2Lost = hasLost(boardPlayer2);

    if (player1Lost && player2Lost) {
        std::cerr << "Somehow, both players lost simultaneously\n";
        std::exit(EXIT_FAILURE);
    } else if (player1Lost)
        return 1;
    else if (player2Lost)
        return 2;
    else
        return 0;
}

bool doPlayerTurn(BoardType& computerBoard) {
    clearScreen();
    std::cout << "Your enemy's ships:\n";
    printGameBoard(computerBoard, defaultTranslationTable());
    std::cout << '\n';

    // Repeat input until a valid pair of coordinates was entered
    while (true) {
        std::cout << "Where do you want to shoot? ";
        std::string userInput{};
        std::getline(std::cin, userInput);
        auto& target =
            getRefFromPoint(computerBoard, inputTranslator(userInput));

        switch (target) {
            case FieldValue::MISS:
                [[fallthrough]];
            case FieldValue::SHIP_HIT:
                std::cout << "You already shot there once!\n";
                continue;
            case FieldValue::EMPTY:
                [[fallthrough]];
            case FieldValue::PLACEHOLDER:
                target = FieldValue::MISS;
                return false;
            case FieldValue::SHIP:
                target = FieldValue::SHIP_HIT;
                return true;
            default:
                std::cerr << "Invalid state of field on board. Terminating!\n";
                std::exit(EXIT_FAILURE);
        }
    }
}

bool doComputerTurn(BoardType& playerBoard) {
    clearScreen();
    const auto result = aiShotRandom(playerBoard);
    std::cout << "Your ships:\n";
    printGameBoard(playerBoard, transparentTranslationTable());
    return result;
}

void waitForEnter() {
    // Emit notice to stdout
    std::puts("Press Enter to continue...");
    std::fflush(stdout);

    while (true) {
        switch (std::getchar()) {
            case '\n':
            case EOF:
                return;
            default:
                continue;
        }
    }
}

WinnerID playGame(BoardType& playerBoard, BoardType& computerBoard) {
    // Loop until a winner is determined and returned
    while (true) {
        if (doPlayerTurn(computerBoard)) {
            std::cout << "Hit!\n";

            // If a hit occured, we need to check for a winner
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        } else
            std::cout << "Miss.\n";
        waitForEnter();

        if (doComputerTurn(playerBoard)) {
            std::cout << "You were hit!\n";

            // If a hit occured, we need to check for a winner
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        } else
            std::cout << "The enemy missed.\n";
        waitForEnter();
    }
}