// SPDX-License-Identifier: GPL-3.0-or-later
/*
SchiffeVersenken - An implementation of Battleships
Copyright (C) 2022 SchiffeVersenken contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
bool doPlayerTurn(BoardType& computerBoard, BoardType& playerBoard) {
    refreshBoard(playerBoard, computerBoard, computerBoard,
                 "Your enemies ships:", defaultTranslationTable());
    // Repeat input until a valid pair of coordinates was entered
    while (true) {
        std::cout << "Where do you want to shoot? ";
        std::string userInput = getLineFromUser();

        if (userInput.empty())
            continue;

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
bool doComputerTurn(BoardType& playerBoard, BoardType& computerBoard) {
    const auto result = aiShotRandom(playerBoard);
    refreshBoard(playerBoard, computerBoard, playerBoard,
                 "Your ships:", transparentTranslationTable());
    return result;
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
        while (doPlayerTurn(computerBoard, playerBoard)) {
            refreshBoard(playerBoard, computerBoard, computerBoard,
                         "Your enemies ships:", defaultTranslationTable());
            std::cout << "Hit!\n";

            // If a hit occured, we need to check if that ends the game
            const auto potentialWinnerID =
                checkWinner(playerBoard, computerBoard);
            if (potentialWinnerID)
                return potentialWinnerID;
        }

        refreshBoard(playerBoard, computerBoard, computerBoard,
                     "Your enemies ships:", defaultTranslationTable());
        std::cout << "Miss.\n";

        waitForReturn();

        if (doComputerTurn(playerBoard, computerBoard)) {
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

WinnerID playGame(BoardType&& playerBoard, BoardType&& computerBoard) {
    return playGame(playerBoard, computerBoard);
}
