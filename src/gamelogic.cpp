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

/*
    Outputs basic program name and version to screen
*/
void writeProgramInfo(std::ostream& out) {
    out << "SchiffeVersenken " << GlobalConf.version << '\n' << std::endl;
}

/*
    Used to update the board on screen
*/
void refreshBoard(const BoardType& board,
                  const char* const boardDiscription,
                  OutputTranslationTable translationTable) {
    clearScreen();
    writeProgramInfo(std::cout);
    std::cout << boardDiscription << '\n';
    printGameBoard(board, translationTable);
    std::cout << '\n';
}

/*
    Scans if any ship parts on the given game board are still intact
*/
static bool hasLost(const BoardType& board) {
    for (const auto& segment : board)
        if (std::find(segment.begin(), segment.end(), FieldValue::SHIP) !=
            segment.end())
            // Contains >= 1 ship parts
            return false;

    // No ships are left
    return true;
}

/*
    Function was reused from @jotoho's weekly exercise code

    Gets a line of text from STDIN and checks for things like EOF or other
    errors.

    Only used here, so we marked it static
*/
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

/*
    Determines the winner, if any, using the hasLost function.

    Return value is 0, when no one has won. Otherwise, the player's numerical
   id.
*/
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

/*
    Do everything needed for the player to take one shot.

    Parameter is the board of the opponent.

    Return value if false, if the shot was a miss.
    Otherwise, it is true.
*/
bool doPlayerTurn(BoardType& computerBoard) {
    refreshBoard(computerBoard,
                 "Your enemies ships:", defaultTranslationTable());
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

/*
    Do everything needed for the computer to shoot in this turn
    (This code will shoot multiple times when the previous shots
    in this turn were successful.)

    Return value: true if the enemy was shot at least once.
                  false if the first shot already missed.
*/
bool doComputerTurn(BoardType& playerBoard) {
    const auto result = aiShotRandom(playerBoard);
    refreshBoard(playerBoard, "Your ships:", transparentTranslationTable());
    return result;
}

/*
    Wait for the player to confirm by pressing Return (LF).

    All other inputs until then are ignored.
*/
void waitForReturn() {
    // Emit notice to stdout
    std::puts("Press Return key to continue...");
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

/*
    The actual game logic.

    This function gets the board of both players and loops through the different
   turns until one of the players wins.

    Then it returns the winner's ID to the calling function for announcement.

    If the game ever reaches an unrecoverable state, the application may be
   terminated.
*/
WinnerID playGame(BoardType& playerBoard, BoardType& computerBoard) {
    if (hasLost(playerBoard) && hasLost(computerBoard))
        throw std::logic_error{"FATAL: No ships were generated!\n"};

    // Loop until a winner is determined and returned
    while (true) {
        while (doPlayerTurn(computerBoard)) {
            refreshBoard(computerBoard,
                         "Your enemies ships:", defaultTranslationTable());
            std::cout << "Hit!\n";

            // If a hit occured, we need to check if that ends the game
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        }

        refreshBoard(computerBoard,
                     "Your enemies ships:", defaultTranslationTable());
        std::cout << "Miss.\n";

        waitForReturn();

        if (doComputerTurn(playerBoard)) {
            std::cout << "You were hit!\n";

            // If a hit occured, we need to check if that ends the game
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        } else
            std::cout << "The enemy missed.\n";

        waitForReturn();
    }
}
