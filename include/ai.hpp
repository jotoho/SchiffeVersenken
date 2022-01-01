#ifndef INCLUDE_GUARD_AI_HPP
#define INCLUDE_GUARD_AI_HPP

#include "./boardpoint.hpp"

bool aiShotRandom(BoardType& board);
void hitShip(BoardType& board, const BoardPoint& lastShot);

#endif  // INCLUDE_GUARD_AI_HPP
