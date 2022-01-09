#ifndef INCLUDE_GUARD_BOARDGEN_HPP
#define INCLUDE_GUARD_BOARDGEN_HPP

#include "./fieldinfo.hpp"

// Returns an empty gameboard (all field set to EMPTY)
BoardType generateGameBoardEmpty();
// Return a randomly populated game board
BoardType generateGameBoardRandom();

#endif  // INCLUDE_GUARD_BOARDGEN_HPP
