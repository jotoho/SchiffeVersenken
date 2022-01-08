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

void refreshBoard(const BoardType& board,
                  const char* const boardDiscription,
                  OutputTranslationTable translationTable) {
    clearScreen();
    writeProgramInfo(std::cout);
    std::cout << boardDiscription << '\n';
    printGameBoard(board, translationTable);
    std::cout << '\n';
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

static std::string getLineFromUser() {
    std::string input;
    while (true) {
        if (std::cin.eof()) {
            std::cerr << "\nSTDIN has been closed and the game cannot continue!"
                      << std::endl;
            std::exit(EXIT_SUCCESS);
        } else if (std::cin.good()) {
            std::getline(std::cin, input);
            if (!std::cin.fail())
                break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return input;
}

WinnerID checkWinner(const BoardType& boardPlayer1,
                     const BoardType& boardPlayer2) {
    const bool player1Lost = hasLost(boardPlayer1);
    const bool player2Lost = hasLost(boardPlayer2);

    if (player1Lost && player2Lost) {
        std::cerr << "Somehow, both players lost simultaneously\n"
                     "Please report this to the developers!\n";
        std::exit(EXIT_FAILURE);
    } else if (player1Lost)
        return 1;
    else if (player2Lost)
        return 2;
    else
        return 0;
}

bool doPlayerTurn(BoardType& computerBoard) {
    refreshBoard(computerBoard, "Your enemies ships",
                 defaultTranslationTable());
    // Repeat input until a valid pair of coordinates was entered
    while (true) {
        std::cout << "Where do you want to shoot? ";
        std::string userInput = getLineFromUser();

        try {
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
                    std::cerr
                        << "Invalid state of field on board. Terminating!\n";
                    std::exit(EXIT_FAILURE);
            }
        } catch (const std::invalid_argument& unused) {
            std::cout << "Please enter valid coordinates!\n";
        }
    }
}

bool doComputerTurn(BoardType& playerBoard) {
    const auto result = aiShotRandom(playerBoard);
    refreshBoard(playerBoard, "Your ships:", transparentTranslationTable());
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
    if (hasLost(playerBoard) && hasLost(computerBoard))
        throw std::logic_error{
            "FATAL: No ships were generated!\n"};
    // Loop until a winner is determined and returned
    while (true) {
        bool playerHitOnce = false;
        while (doPlayerTurn(computerBoard)) {
            refreshBoard(computerBoard, "Your enemies ships",
                         defaultTranslationTable());
            std::cout << "Hit!\n";
            playerHitOnce = true;

            // If a hit occured, we need to check if that ends the game
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        }

        if (!playerHitOnce) {
            refreshBoard(computerBoard, "Your enemies ships",
                         defaultTranslationTable());
            std::cout << "Miss.\n";
        }
        waitForEnter();

        if (doComputerTurn(playerBoard)) {
            std::cout << "You were hit!\n";

            // If a hit occured, we need to check if that ends the game
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        } else
            std::cout << "The enemy missed.\n";
        waitForEnter();
    }
}
