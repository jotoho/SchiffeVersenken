#ifndef INCLUDE_GUARD_GAMELOGIC_HPP
#define INCLUDE_GUARD_GAMELOGIC_HPP

#include <cstdint>
#include <iostream>
#include "./fieldinfo.hpp"

using WinnerID = std::uint_least8_t;

std::uint_least8_t checkWinner(const BoardType& boardPlayer1,
                               const BoardType& boardPlayer2);

void writeProgramInfo(std::ostream& out = std::cout);
bool doPlayerTurn(BoardType& computerBoard);
bool doComputerTurn(BoardType& playerBoard);
void waitForEnter();
WinnerID playGame(BoardType& playerBoard, BoardType& computerBoard);

#endif  // INCLUDE_GUARD_GAMELOGIC_HPP
