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
